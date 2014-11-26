/*
 * Helper functions that aren't direct I/O.
 */

#include "MPIHook.h"

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
int MPI_File_delete(char *filename, MPI_Info info)
{
	char fsname[BUF_SIZE];
	char hdfs_filename[BUF_SIZE];
	hdfsFile file;
	struct hdfsBuilder *builder;
	hdfsFS fs;

	status("File_delete called.\n");

	if (hdfs_url_parse(filename, fsname, BUF_SIZE, hdfs_filename, BUF_SIZE)) {
		int (*real_MPI_File_delete)(char *, MPI_Info) = NULL;
		real_MPI_File_delete = dlsym(RTLD_NEXT, "MPI_File_delete");
		if (!real_MPI_File_delete) {
			fprintf(stderr, "Failed to load actual MPI_File_open location.\n");
			return -1;
		}
		status("Passing File_delete call to actual MPI function.\n");
		return real_MPI_File_delete(filename, info);
	}

	builder = hdfsNewBuilder();
	if (!builder) {
		fprintf(stderr, "Failed to make new hdfsBuilder.\n");
		return -1;
	}

	hdfsBuilderSetNameNode(builder, fsname);

	fs = hdfsBuilderConnect(builder);
	if (!fs) {
		fprintf(stderr, "Failed to connect to hdfs.\n");
		return -1;
	}

	return hdfsDelete(fs, hdfs_filename, 1);
}
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

int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence)
{
	hdfsFile_wrapper *fh_w;
	
	status("File_seek called.\n");

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_seek)(MPI_File, MPI_Offset, int) = NULL;
		real_MPI_File_seek = dlsym(RTLD_NEXT, "MPI_File_seek");
		if (!real_MPI_File_seek) {
			fprintf(stderr, "Failed to load actual MPI_File_seek location.\n");
			return -1;
		}

		status("Passing File_seek to actual MPI function.\n");
		return real_MPI_File_seek(fh, offset, whence);
	}

	if (whence == MPI_SEEK_SET) {
		if (hdfsSeek(fh_w->fs, fh_w->file, offset)) {
			fprintf(stderr, "Failed to seek in hdfs file.\n");
			return -1;
		}
	}
	else if (whence == MPI_SEEK_CUR) {
		tOffset cur_off = hdfsTell(fh_w->fs, fh_w->file);
		if (offset == -1) {
			fprintf(stderr, "Failed to tell for seek in hdfs file.\n");
			return -1;
		}
		if (hdfsSeek(fh_w->fs, fh_w->file, cur_off + offset)) {
			fprintf(stderr, "Failed to seek in hdfs file.\n");
			return -1;
		}
	}
	else {
		fprintf(stderr, "Operation not supported.\n");
		return -1;
	}
		
	return MPI_SUCCESS;
}
int MPI_File_get_position(MPI_File fh, MPI_Offset *offset)
{
	hdfsFile_wrapper *fh_w;
	tOffset cur_off;
	
	status("File_get_byte_offset called.\n");

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_get_position)(MPI_File, MPI_Offset *) = NULL;
		real_MPI_File_get_position = dlsym(RTLD_NEXT, "MPI_File_get_position");
		if (!real_MPI_File_get_position) {
			fprintf(stderr, "Failed to load actual MPI_File_get_position location.\n");
			return -1;
		}

		status("Passing File_get_position to actual MPI function.\n");
		return real_MPI_File_get_position(fh, offset);
	}

	cur_off = hdfsTell(fh_w->fs, fh_w->file);
	if (cur_off == -1) {
		fprintf(stderr, "Failed to get position in hdfs file.\n");
		return -1;
	}

	*offset = cur_off;

	return MPI_SUCCESS;
}
int MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp) { NOT_IMPLEMENTED; }
