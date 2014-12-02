#include "MPIHook.h"

/*
 * File operations that are not currently supported.
 */

int MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }
int MPI_File_iwrite(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }

int MPI_File_read_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_write_shared(MPI_File fh, const void *buf, int count, MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_iread_shared(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }
int MPI_File_iwrite_shared(MPI_File fh, const void *buf, int count, 
			   MPI_Datatype datatype, MPIO_Request *request) { NOT_IMPLEMENTED; }
int MPI_File_read_ordered(MPI_File fh, void *buf, int count, 
                          MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_write_ordered(MPI_File fh, const void *buf, int count, 
                           MPI_Datatype datatype, MPI_Status *status) { NOT_IMPLEMENTED; }
int MPI_File_seek_shared(MPI_File fh, MPI_Offset offset, int count);
int MPI_File_get_position_shared(MPI_File fh, MPI_Offset *ofsfet) { NOT_IMPLEMENTED; }

int MPI_File_read_at_all_begin(MPI_File, MPI_Offset, void *,
                               int, MPI_Datatype);
int MPI_File_read_at_all_end(MPI_File, void *, MPI_Status *);
int MPI_File_write_at_all_begin(MPI_File, MPI_Offset, const void *,
                                int, MPI_Datatype);
int MPI_File_write_at_all_end(MPI_File, const void *, MPI_Status *);
int MPI_File_read_all_begin(MPI_File, void *, int, MPI_Datatype);
int MPI_File_read_all_end(MPI_File, void *, MPI_Status *);
int MPI_File_write_all_begin(MPI_File, const void *, int, MPI_Datatype);
int MPI_File_write_all_end(MPI_File, const void *, MPI_Status *);
int MPI_File_read_ordered_begin(MPI_File, void *, int, MPI_Datatype);
int MPI_File_read_ordered_end(MPI_File, void *, MPI_Status *);
int MPI_File_write_ordered_begin(MPI_File, const void *, int, MPI_Datatype);
int MPI_File_write_ordered_end(MPI_File, const void *, MPI_Status *);

int MPI_File_get_type_extent(MPI_File, MPI_Datatype, MPI_Aint *);

int MPI_Register_datarep(const char *,
			 MPI_Datarep_conversion_function *,
			 MPI_Datarep_conversion_function *,
			 MPI_Datarep_extent_function *,
			 void *);

int MPI_File_set_atomicity(MPI_File, int);
int MPI_File_get_atomicity(MPI_File, int *);
int MPI_File_sync(MPI_File);
