#include "MPIHook.h"

/*
 * File operations that are not currently supported.
 */

int MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPIO_Request *request)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_iread)(MPI_File, void *, int, MPI_Datatype, MPI_Request*) = NULL;
		real_MPI_File_iread = dlsym(RTLD_NEXT, "MPI_File_iread");
		if (!real_MPI_File_iread)
			fprintf(stderr, "Failed to load actual MPI_File_iread location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_iread to actual MPI function.\n");
		return real_MPI_File_iread(fh, buf, count, datatype, request);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_iwrite(MPI_File fh, MPIHDFS_CONST void *buf, int count, 
		    MPI_Datatype datatype, MPIO_Request *request)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_iwrite)(MPI_File, MPIHDFS_CONST void *, int, MPI_Datatype, MPI_Request*) = NULL;
		real_MPI_File_iwrite = dlsym(RTLD_NEXT, "MPI_File_iwrite");
		if (!real_MPI_File_iwrite)
			fprintf(stderr, "Failed to load actual MPI_File_iwrite location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_iwrite to actual MPI function.\n");
		return real_MPI_File_iwrite(fh, buf, count, datatype, request);
	}
	
	NOT_IMPLEMENTED;
}

int MPI_File_read_shared(MPI_File fh, void *buf, int count, 
			 MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_read_shared)(MPI_File, void *, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_read_shared = dlsym(RTLD_NEXT, "MPI_File_read_shared");
		if (!real_MPI_File_read_shared)
			fprintf(stderr, "Failed to load actual MPI_File_read_shared location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_read_shared to actual MPI function.\n");
		return real_MPI_File_read_shared(fh, buf, count, datatype, status);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_write_shared(MPI_File fh, MPIHDFS_CONST void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_write_shared)(MPI_File, MPIHDFS_CONST void *, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_write_shared = dlsym(RTLD_NEXT, "MPI_File_write_shared");
		if (!real_MPI_File_write_shared)
			fprintf(stderr, "Failed to load actual MPI_File_write_shared location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_write_shared to actual MPI function.\n");
		return real_MPI_File_write_shared(fh, buf, count, datatype, status);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPIO_Request *request)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_iread_shared)(MPI_File, void *, int, MPI_Datatype, MPI_Request*) = NULL;
		real_MPI_File_iread_shared = dlsym(RTLD_NEXT, "MPI_File_iread_shared");
		if (!real_MPI_File_iread_shared)
			fprintf(stderr, "Failed to load actual MPI_File_iread_shared location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_iread_shared to actual MPI function.\n");
		return real_MPI_File_iread_shared(fh, buf, count, datatype, request);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_iwrite_shared(MPI_File fh, MPIHDFS_CONST void *buf, int count, 
			   MPI_Datatype datatype, MPIO_Request *request)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_iwrite_shared)(MPI_File, MPIHDFS_CONST void *, int, MPI_Datatype, MPI_Request*) = NULL;
		real_MPI_File_iwrite_shared = dlsym(RTLD_NEXT, "MPI_File_iwrite_shared");
		if (!real_MPI_File_iwrite_shared)
			fprintf(stderr, "Failed to load actual MPI_File_iwrite_shared location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_iwrite_shared to actual MPI function.\n");
		return real_MPI_File_iwrite_shared(fh, buf, count, datatype, request);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_read_ordered(MPI_File fh, void *buf, int count, 
                          MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_read_ordered)(MPI_File, void *, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_read_ordered = dlsym(RTLD_NEXT, "MPI_File_read_ordered");
		if (!real_MPI_File_read_ordered)
			fprintf(stderr, "Failed to load actual MPI_File_read_ordered location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_read_ordered to actual MPI function.\n");
		return real_MPI_File_read_ordered(fh, buf, count, datatype, status);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_write_ordered(MPI_File fh, MPIHDFS_CONST void *buf, int count, 
                           MPI_Datatype datatype, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_write_ordered)(MPI_File, MPIHDFS_CONST void *, int, MPI_Datatype, MPI_Status*) = NULL;
		real_MPI_File_write_ordered = dlsym(RTLD_NEXT, "MPI_File_write_ordered");
		if (!real_MPI_File_write_ordered)
			fprintf(stderr, "Failed to load actual MPI_File_write_ordered location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_write_ordered to actual MPI function.\n");
		return real_MPI_File_write_ordered(fh, buf, count, datatype, status);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int count)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_seek_shared)(MPI_File, MPI_Offset, int) = NULL;
		real_MPI_File_seek_shared = dlsym(RTLD_NEXT, "MPI_File_seek_shared");
		if (!real_MPI_File_seek_shared)
			fprintf(stderr, "Failed to load actual MPI_File_seek_shared location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_seek_shared to actual MPI function.\n");
		return real_MPI_File_seek_shared(fh, offset, count);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_get_position_shared(MPI_File fh, MPI_Offset *offset)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_get_position_shared)(MPI_File, MPI_Offset*) = NULL;
		real_MPI_File_get_position_shared = dlsym(RTLD_NEXT, "MPI_File_get_position_shared");
		if (!real_MPI_File_get_position_shared)
			fprintf(stderr, "Failed to load actual MPI_File_get_position_shared location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_get_position_shared to actual MPI function.\n");
		return real_MPI_File_get_position_shared(fh, offset);
	}
	
	NOT_IMPLEMENTED;
}

int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void *buf,
                               int count, MPI_Datatype datatype)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_read_at_all_begin)(MPI_File, MPI_Offset, void *, int, MPI_Datatype) = NULL;
		real_MPI_File_read_at_all_begin = dlsym(RTLD_NEXT, "MPI_File_read_at_all_begin");
		if (!real_MPI_File_read_at_all_begin)
			fprintf(stderr, "Failed to load actual MPI_File_read_at_all_begin location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_read_at_all_begin to actual MPI function.\n");
		return real_MPI_File_read_at_all_begin(fh, offset, buf, count, datatype);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_read_at_all_end(MPI_File fh, void *buf, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_read_at_all_end)(MPI_File, void *, MPI_Status *) = NULL;
		real_MPI_File_read_at_all_end = dlsym(RTLD_NEXT, "MPI_File_read_at_all_end");
		if (!real_MPI_File_read_at_all_end)
			fprintf(stderr, "Failed to load actual MPI_File_read_at_all_end location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_read_at_all_end to actual MPI function.\n");
		return real_MPI_File_read_at_all_end(fh, buf, status);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, MPIHDFS_CONST void *buf,
                                int count, MPI_Datatype datatype)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_write_at_all_begin)(MPI_File, MPI_Offset, MPIHDFS_CONST void *, int, MPI_Datatype) = NULL;
		real_MPI_File_write_at_all_begin = dlsym(RTLD_NEXT, "MPI_File_write_at_all_begin");
		if (!real_MPI_File_write_at_all_begin)
			fprintf(stderr, "Failed to load actual MPI_File_write_at_all_begin location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_write_at_all_begin to actual MPI function.\n");
		return real_MPI_File_write_at_all_begin(fh, offset, buf, count, datatype);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_write_at_all_end(MPI_File fh, MPIHDFS_CONST void *buf, MPI_Status *status)
{
	hdfsFile_wrapper *fh_w;
	
	if (!fh)
		return MPI_ERR_ARG;

	fh_w = (hdfsFile_wrapper*)fh;

	if (fh_w->magic != HDFSFILEMAGIC)
	{
		int (*real_MPI_File_write_at_all_end)(MPI_File, MPIHDFS_CONST void *, MPI_Status *) = NULL;
		real_MPI_File_write_at_all_end = dlsym(RTLD_NEXT, "MPI_File_write_at_all_end");
		if (!real_MPI_File_write_at_all_end)
			fprintf(stderr, "Failed to load actual MPI_File_write_at_all_end location.\n");
			return MPI_ERR_OTHER;

		status("Passing File_write_at_all_end to actual MPI function.\n");
		return real_MPI_File_write_at_all_end(fh, buf, status);
	}
	
	NOT_IMPLEMENTED;
}
int MPI_File_read_all_begin(MPI_File, void *, int, MPI_Datatype);
int MPI_File_read_all_end(MPI_File, void *, MPI_Status *);
int MPI_File_write_all_begin(MPI_File, MPIHDFS_CONST void *, int, MPI_Datatype);
int MPI_File_write_all_end(MPI_File, MPIHDFS_CONST void *, MPI_Status *);
int MPI_File_read_ordered_begin(MPI_File, void *, int, MPI_Datatype);
int MPI_File_read_ordered_end(MPI_File, void *, MPI_Status *);
int MPI_File_write_ordered_begin(MPI_File, MPIHDFS_CONST void *, int, MPI_Datatype);
int MPI_File_write_ordered_end(MPI_File, MPIHDFS_CONST void *, MPI_Status *);

int MPI_File_get_type_extent(MPI_File, MPI_Datatype, MPI_Aint *);

int MPI_Register_datarep(MPIHDFS_CONST char *,
			 MPI_Datarep_conversion_function *,
			 MPI_Datarep_conversion_function *,
			 MPI_Datarep_extent_function *,
			 void *);

int MPI_File_set_atomicity(MPI_File, int);
int MPI_File_get_atomicity(MPI_File, int *);
int MPI_File_sync(MPI_File);
