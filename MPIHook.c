#define _GNU_SOURCE

#include "hdfs.h"
#include "hdfs_url.h"
#include <mpi.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>

#define DEBUG

#ifdef DEBUG
#define status(str, ...) printf(str, ##__VA_ARGS__)
#else
#define status(str)
#endif

#define HDFSFILEMAGIC 0x19d48be3
#define BUF_SIZE 4096

#define NOT_IMPLEMENTED { fprintf(stderr, "Function not implemented.\n"); return -1; }

typedef struct
{
	int32_t magic;
	hdfsFS fs;
	hdfsFile file;
	char *filename;
	int amode;
} hdfsFile_wrapper;

int MPI_File_open(MPI_Comm comm, char *filename, int amode,
		  MPI_Info info, MPI_File *fh)
{
	char fsname[BUF_SIZE];
	char hdfs_filename[BUF_SIZE];
	hdfsFile_wrapper *fh_w;
	hdfsFile file;
	struct hdfsBuilder *builder;
	hdfsFS fs;

	status("File_open called.\n");

	if (hdfs_url_parse(filename, fsname, BUF_SIZE, hdfs_filename, BUF_SIZE)) {
		int (*real_MPI_File_open)(MPI_Comm, const char*, int, MPI_Info, MPI_File *) = NULL;
		real_MPI_File_open = dlsym(RTLD_NEXT, "MPI_File_open");
		if (!real_MPI_File_open) {
			fprintf(stderr, "Failed to load actual MPI_File_open location.\n");
			return -1;
		}
		status("Passing File_open call to actual MPI function.\n");
		return real_MPI_File_open(comm, filename, amode, info, fh);
	}

	if (amode != MPI_MODE_RDONLY) {
		fprintf(stderr, "Only reading from HDFS is supported currently.\n");
		return -1;
	}

	fh_w = malloc(sizeof(hdfsFile_wrapper));
	if (!fh) {
		fprintf(stderr, "Malloc failed.\n");
		return -1;
	}

	fh_w->magic = HDFSFILEMAGIC;

	builder = hdfsNewBuilder();
	if (!builder) {
		fprintf(stderr, "Failed to make new hdfsBuilder.\n");
		free(fh_w);		
		return -1;
	}

	hdfsBuilderSetNameNode(builder, fsname);

	fs = hdfsBuilderConnect(builder);
	if (!fs) {
		fprintf(stderr, "Failed to connect to hdfs.\n");
		free(fh_w);		
		return -1;
	}

	file = hdfsOpenFile(fs, hdfs_filename, O_RDONLY, 0, 0, 0);
	if (!file) {
		fprintf(stderr, "Failed to open hdfs file.\n");
		free(fh_w);
		return -1;
	}	

	fh_w->filename = malloc(strlen(hdfs_filename) + 1);
	if (!fh_w->filename) {
		fprintf(stderr, "Failed to allocate space for filename.\n");
		free(fh_w);
		return -1;
	}

	strcpy(fh_w->filename, hdfs_filename);

	fh_w->fs = fs;
	fh_w->file = file;
	fh_w->amode = amode;
	*fh = (MPI_File)fh_w;

	status("File_open returning successfully.\n");

	return MPI_SUCCESS;
}

int MPI_File_close(MPI_File *fh)
{
	hdfsFile_wrapper *fh_w;
	int ret;

	status("File_close called.\n");
	
	fh_w = (hdfsFile_wrapper*)*fh;

	if (fh_w->magic != HDFSFILEMAGIC) {
		int (*real_MPI_File_close)(MPI_File *) = NULL;
		real_MPI_File_close = dlsym(RTLD_NEXT, "MPI_File_close");
		if (!real_MPI_File_close) {
			fprintf(stderr, "Failed to load actual MPI_File_close location.\n");
			return -1;
		}
		status("Passing File_close to actual MPI function.\n");
		return real_MPI_File_close(fh);
	}

	status("HDFS file found in File_close.\n");

	ret = hdfsCloseFile(fh_w->fs, fh_w->file);

	if (ret) {
		fprintf(stderr, "Failed to close hdfs file.\n");
		return -1;
	}

	free(fh_w->filename);
	free(fh_w);

	status("File_close returning successfully.\n");

	return MPI_SUCCESS;
}
int MPI_File_delete(char *filename, MPI_Info info) { NOT_IMPLEMENTED; }
int MPI_File_set_size(MPI_File fh, MPI_Offset size) { NOT_IMPLEMENTED; }
int MPI_File_preallocate(MPI_File fh, MPI_Offset size) { NOT_IMPLEMENTED; }
int MPI_File_get_size(MPI_File fh, MPI_Offset *size)
{
	hdfsFile_wrapper *fh_w;
	
	status("File_get_size called.\n");

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_get_size)(MPI_File, MPI_Offset*) = NULL;
		real_MPI_File_get_size = dlsym(RTLD_NEXT, "MPI_File_get_size");
		if (!real_MPI_File_get_size) {
			fprintf(stderr, "Failed to load actual MPI_File_get_size location.\n");
			return -1;
		}

		status("Passing File_get_size to actual MPI function.\n");
		return real_MPI_File_get_size(fh, size);
	}

	hdfsFileInfo *fileInfo = hdfsGetPathInfo(fh_w->fs, fh_w->filename);
	if (!fileInfo) {
		fprintf(stderr, "Failed to get path info for file size.\n");
		return -1;
	}	

	*size = fileInfo->mSize;

	hdfsFreeFileInfo(fileInfo, 1);

	return MPI_SUCCESS;
}
int MPI_File_get_group(MPI_File fh, MPI_Group *group) { NOT_IMPLEMENTED; }
int MPI_File_get_amode(MPI_File fh, int *amode)
{
	hdfsFile_wrapper *fh_w;
	
	status("File_get_amode called.\n");

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_get_amode)(MPI_File, int *amode) = NULL;
		real_MPI_File_get_amode = dlsym(RTLD_NEXT, "MPI_File_get_amode");
		if (!real_MPI_File_get_amode) {
			fprintf(stderr, "Failed to load actual MPI_File_get_size location.\n");
			return -1;
		}

		status("Passing File_get_size to actual MPI function.\n");
		return real_MPI_File_get_amode(fh, amode);
	}

	*amode = fh_w->amode;
	return MPI_SUCCESS;
}

int MPI_File_set_info(MPI_File fh, MPI_Info info) { NOT_IMPLEMENTED; }
int MPI_File_get_info(MPI_File fh, MPI_Info *info) { NOT_IMPLEMENTED; }

/* Section 9.3 */
int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype,
	         MPI_Datatype filetype, char *datarep, MPI_Info info) { NOT_IMPLEMENTED; }
int MPI_File_get_view(MPI_File fh, MPI_Offset *disp, 
                 MPI_Datatype *etype, MPI_Datatype *filetype, char *datarep) { NOT_IMPLEMENTED; }

/* Section 9.4.2 */
int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	int ret, size;
	
	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_read_at)(MPI_File, MPI_Offset, void*, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_read_at = dlsym(RTLD_NEXT, "MPI_File_read_at");
		if (!real_MPI_File_read_at)
			fprintf(stderr, "Failed to load actual MPI_File_close location.\n");
			return -1;

		status("Passing File_read_at to actual MPI function.\n");
		return real_MPI_File_read_at(fh, offset, buf, count, datatype, status);
	}

	status("HDFS file found in File_read_at.\n");

	MPI_Type_size(datatype, &size);

	status("Got type size: %d.\n", size);
	status("Offset: %d\n", offset);

	ret = hdfsPread(fh_w->fs, fh_w->file, offset, buf, size * count);

	status("Guessing I'm not gonna get here?\n");

	if (ret == -1)
		return -1;

	return MPI_SUCCESS;
}

int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_write_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }
int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }

/* Section 9.4.3 */
int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	int ret, size;
	
	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_read)(MPI_File, void*, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_read = dlsym(RTLD_NEXT, "MPI_File_read_at");
		if (!real_MPI_File_read)
			fprintf(stderr, "Failed to load actual MPI_File_close location.\n");
			return -1;

		status("Passing File_read to actual MPI function.\n");
		return real_MPI_File_read(fh, buf, count, datatype, status);
	}

	status("HDFS file found in File_read_at.\n");

	MPI_Type_size(datatype, &size);

	status("Got type size: %d.\n", size);

	ret = hdfsRead(fh_w->fs, fh_w->file, buf, size * count);

	if (ret == -1)
		return -1;

	return MPI_SUCCESS;

}
int MPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; } 
int MPI_File_write(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_write_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

int MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }
int MPI_File_iwrite(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }

int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence) { NOT_IMPLEMENTED; }
int MPI_File_get_position(MPI_File fh, MPI_Offset *offset) { NOT_IMPLEMENTED; }
int MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp) { NOT_IMPLEMENTED; }

/* Section 9.4.4 */
int MPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_write_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }
int MPI_File_iwrite_shared(MPI_File fh, void *buf, int count, 
			   MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }
int MPI_File_read_ordered(MPI_File fh, void *buf, int count, 
                          MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_write_ordered(MPI_File fh, void *buf, int count, 
                           MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int count);
int MPI_File_get_position_shared(MPI_File fh, MPI_Offset *ofsfet) { NOT_IMPLEMENTED; }

/* Section 9.4.5 */
int MPI_File_read_at_all_begin(MPI_File, MPI_Offset, void *,
                               int, MPI_Datatype);
int MPI_File_read_at_all_end(MPI_File, void *, MPI_Status *);
int MPI_File_write_at_all_begin(MPI_File, MPI_Offset, void *,
                                int, MPI_Datatype);
int MPI_File_write_at_all_end(MPI_File, void *, MPI_Status *);
int MPI_File_read_all_begin(MPI_File, void *, int, MPI_Datatype);
int MPI_File_read_all_end(MPI_File, void *, MPI_Status *);
int MPI_File_write_all_begin(MPI_File, void *, int, MPI_Datatype);
int MPI_File_write_all_end(MPI_File, void *, MPI_Status *);
int MPI_File_read_ordered_begin(MPI_File, void *, int, MPI_Datatype);
int MPI_File_read_ordered_end(MPI_File, void *, MPI_Status *);
int MPI_File_write_ordered_begin(MPI_File, void *, int, MPI_Datatype);
int MPI_File_write_ordered_end(MPI_File, void *, MPI_Status *);

/* Section 9.5.1 */
int MPI_File_get_type_extent(MPI_File, MPI_Datatype, MPI_Aint *);

/* Section 9.5.3 */
int MPI_Register_datarep(char *,
			 MPI_Datarep_conversion_function *,
			 MPI_Datarep_conversion_function *,
			 MPI_Datarep_extent_function *,
			 void *);

/* Section 9.6.1 */
int MPI_File_set_atomicity(MPI_File, int);
int MPI_File_get_atomicity(MPI_File, int *);
int MPI_File_sync(MPI_File);




