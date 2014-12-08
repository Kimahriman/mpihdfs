/*
 * Synchronous I/O functions
 */

#include "MPIHook.h"

/*
 * Performs a read at a specific offset in the file
 */
int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	int ret, size;

	if (!fh)
		return MPI_ERR_ARG;
	
	fh_w = (hdfsFile_wrapper*)fh;


	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_read_at)(MPI_File, MPI_Offset, void*, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_read_at = dlsym(RTLD_NEXT, "MPI_File_read_at");
		if (!real_MPI_File_read_at) {
			fprintf(stderr, "Failed to load actual MPI_File_close location.\n");
			return MPI_ERR_OTHER;
		}

		status("Passing File_read_at to actual MPI function.\n");
		return real_MPI_File_read_at(fh, offset, buf, count, datatype, status);
	}

	status("HDFS file found in File_read_at.\n");

#ifdef NO_MPI
	size = 1;
#else
	MPI_Type_size(datatype, &size);
#endif

	status("Got type size: %d.\n", size);
	status("Offset: %d\n", offset);

	ret = hdfsPread(fh_w->fs, fh_w->file, offset, buf, size * count);

	if (ret == -1)
		return MPI_ERR_IO;

	return MPI_SUCCESS;
}

int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_read_at_all)(MPI_File, MPI_Offset, void *, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_read_at_all = dlsym(RTLD_NEXT, "MPI_File_read_at_all");
		if (!real_MPI_File_read_at_all) {
			fprintf(stderr, "Failed to load actual MPI_File_read_at_all location.\n");
			return MPI_ERR_OTHER;
		}

		status("Passing File_readat_all to actual MPI function.\n");
		return real_MPI_File_read_at_all(fh, offset, buf, count, datatype, status);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_write_at(MPI_File fh, MPI_Offset offset, MPIHDFS_CONST void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_write_at)(MPI_File, MPI_Offset, MPIHDFS_CONST void *, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_write_at = dlsym(RTLD_NEXT, "MPI_File_write_at");
		if (!real_MPI_File_write_at) {
			fprintf(stderr, "Failed to load actual MPI_File_write_at location.\n");
			return MPI_ERR_OTHER;
		}

		status("Passing File_write_at to actual MPI function.\n");
		return real_MPI_File_write_at(fh, offset, buf, count, datatype, status);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, MPIHDFS_CONST void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_write_at_all)(MPI_File, MPI_Offset, MPIHDFS_CONST void *, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_write_at_all = dlsym(RTLD_NEXT, "MPI_File_write_at_all");
		if (!real_MPI_File_write_at_all) {
			fprintf(stderr, "Failed to load actual MPI_File_write_at_all location.\n");
			return MPI_ERR_OTHER;
		}

		status("Passing File_write_at_all to actual MPI function.\n");
		return real_MPI_File_write_at_all(fh, offset, buf, count, datatype, status);
	}
	
	NOT_IMPLEMENTED;
}


int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }
int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, MPIHDFS_CONST void *buf,
	      int count, MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }

/*
 * Performs a read based on the current position in the file
 */
int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	int ret, size;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_read)(MPI_File, void*, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_read = dlsym(RTLD_NEXT, "MPI_File_read");
		if (!real_MPI_File_read) {
			fprintf(stderr, "Failed to load actual MPI_File_read location.\n");
			return MPI_ERR_OTHER;
		}

		status("Passing File_read to actual MPI function.\n");
		return real_MPI_File_read(fh, buf, count, datatype, status);
	}

	status("HDFS file found in File_read_at.\n");

#ifdef NO_MPI
	size = 1;
#else
	MPI_Type_size(datatype, &size);
#endif

	status("Got type size: %d.\n", size);

	ret = hdfsRead(fh_w->fs, fh_w->file, buf, size * count);

	if (ret == -1)
		return MPI_ERR_IO;

	return MPI_SUCCESS;

}
int MPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_read_all)(MPI_File, void *, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_read_all = dlsym(RTLD_NEXT, "MPI_File_read_all");
		if (!real_MPI_File_read_all) {
			fprintf(stderr, "Failed to load actual MPI_File_read_all location.\n");
			return MPI_ERR_OTHER;
		}

		status("Passing File_read_all to actual MPI function.\n");
		return real_MPI_File_read_all(fh, buf, count, datatype, status);
	}
	
	NOT_IMPLEMENTED;
}

/*
 * Performs a write based on the current position in the file
 */
int MPI_File_write(MPI_File fh, MPIHDFS_CONST void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	int ret, size, mode;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_write)(MPI_File, MPIHDFS_CONST void*, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_write = dlsym(RTLD_NEXT, "MPI_File_write");
		if (!real_MPI_File_write) {
			fprintf(stderr, "Failed to load actual MPI_File_close location.\n");
			return MPI_ERR_OTHER;
		}

		status("Passing File_write to actual MPI function.\n");
		return real_MPI_File_write(fh, buf, count, datatype, status);
	}

	status("HDFS file found in File_write.\n");

	if (fh_w->file != NULL || !(fh_w->amode & MPI_MODE_WRONLY)) {
		fprintf(stderr, "Write called on a file not open for writing.\n");
		return MPI_ERR_AMODE;
	}

	
	if (!hdfsExists(fh_w->fs, fh_w->filename)) {
		status("Opening file in append mode.\n");
		mode = O_WRONLY | O_APPEND;
	}
	else {
		status("Opening file in create mode.\n");
		mode = O_WRONLY;
	}

	fh_w->file = hdfsOpenFile(fh_w->fs, fh_w->filename, mode, 0, 0, 0);
	if (!fh_w->file) {
		fprintf(stderr, "Failed to open hdfs file for writing.\n");
		return -1;
	}	

	status("Successfully opened hdfs file for writing.\n");

#ifdef NO_MPI
	size = 1;
#else
	MPI_Type_size(datatype, &size);
#endif	

	ret = hdfsWrite(fh_w->fs, fh_w->file, buf, size * count);

	if (ret == -1)
		fprintf(stderr, "Failed to write to hdfs file.\n");

	if (hdfsCloseFile(fh_w->fs, fh_w->file)) {
		fh_w->file = NULL;
		fprintf(stderr, "Failed to close file after hdfs write. errno = %d\n", errno);
		return MPI_ERR_FILE;
	}
	
	fh_w->file = NULL;

	if (ret == -1)
		return MPI_ERR_IO;

	return MPI_SUCCESS;
}
int MPI_File_write_all(MPI_File fh, MPIHDFS_CONST void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_write_all)(MPI_File, MPIHDFS_CONST void *, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_write_all = dlsym(RTLD_NEXT, "MPI_File_write_all");
		if (!real_MPI_File_write_all) {
			fprintf(stderr, "Failed to load actual MPI_File_write_all location.\n");
			return MPI_ERR_OTHER;
		}

		status("Passing File_write_all to actual MPI function.\n");
		return real_MPI_File_write_all(fh, buf, count, datatype, status);
	}
	
	NOT_IMPLEMENTED;
}

