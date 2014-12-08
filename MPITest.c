#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0
static const long LIMIT=1024000;

int main(int argc, char * argv[]) {
	int size, rank;
	int namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Offset file_size;
	MPI_File in, out;
	int err;
	char buf[4096];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);

	fprintf(stdout, "Process %d of %d is on %s\n",
			rank, size, processor_name);
	fflush(stdout);

	err = MPI_File_open(MPI_COMM_WORLD, argv[1], MPI_MODE_RDONLY, MPI_INFO_NULL, &in);
	if (err != MPI_SUCCESS)
	{
		printf("Error: file open. code: %d. \n", err);
		MPI_Finalize();
		exit(-1);
	}

	err = MPI_File_open(MPI_COMM_WORLD, argv[2], MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &out);
	if (err != MPI_SUCCESS)
	{
		printf("Error: file open write. code: %d. \n", err);
		MPI_Finalize();
		exit(-1);
	}

	MPI_File_get_size(in, &file_size);
	
	if (file_size < sizeof(buf)) {
		err = MPI_File_read(in, buf, file_size, MPI_CHAR, MPI_STATUS_IGNORE);
		if (err == -1) {
			printf("Error: file read. code: %d. \n", err);
			MPI_Finalize();
			exit(-1);
		}
		buf[file_size] = 0;
		puts(buf);
	}

	err = MPI_File_close(&in);
	if (err != MPI_SUCCESS)
	{
		printf("Error: file close. code: %d. \n", err);
	}
	err = MPI_File_close(&out);
	if (err != MPI_SUCCESS)
	{
		printf("Error: file close. code: %d. \n", err);
	}

	MPI_Finalize();
	return 0;

}
