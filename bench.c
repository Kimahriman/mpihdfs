#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0
static const long LIMIT=1048576;

MPI_Offset read_file(const int size, const int rank, char * name, int block_size) {
	int err, i;
	double start_read, readtime, end_read, total_time;
	char *chunk;
	MPI_Offset file_size, read_size;
	MPI_File in;

	MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_RDONLY, MPI_INFO_NULL, &in);
	err = MPI_File_get_size(in, &file_size);

	if(err != 0){
		printf("Error: file open. code: %d. \n", err);
		MPI_Finalize();
		exit(1);
	}

	chunk = malloc(block_size * sizeof(char));

	MPI_Barrier(MPI_COMM_WORLD);

	start_read = MPI_Wtime();

	for(i = rank; i < file_size/block_size; i += size){
		read_size = block_size;
		if (i * block_size + block_size > file_size)
			read_size = file_size - i * block_size;
		MPI_File_read_at(in, i * block_size, chunk, read_size, MPI_CHAR, MPI_STATUS_IGNORE);
	}

	end_read = MPI_Wtime();
	readtime=end_read-start_read;
	
	MPI_Reduce(&readtime, &total_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == MASTER) {
		printf("Time for whole read: %.2lf secs.\n", total_time);
		printf("Total size: %lu bytes.\n", (unsigned long)file_size);
		printf("Bandwidth: %.21f MB/s.\n", file_size / (1024*1024) / total_time);
	}
	free(chunk);
	MPI_File_close(&in);
	return file_size;
}

int main(int argc, char * argv[]) {
	int size, rank, block_size;
	int namelen;
	double start=0.0, end;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Offset file_size;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);

	fprintf(stdout, "Process %d of %d is on %s\n",
			rank, size, processor_name);
	fflush(stdout);

	block_size = atoi(argv[2]);

	if (rank == MASTER)
		start=MPI_Wtime();
	
	//process_file(&in, size, rank, &out, argv[1], argv[2]);

	//if (rank == MASTER){
	//	end=MPI_Wtime();
	//	printf("Wallclock time elapsed: %.2lf seconds\n", end-start);
	//}

	file_size = read_file(size, rank, argv[1], block_size);
	//write_file(size, rank, argv[2], file_size);
	if(rank==MASTER){
		end=MPI_Wtime();
		printf("Total wall clock time: %.21lf seconds.\n", end-start);
	}

	MPI_Finalize();
	return 0;

}
