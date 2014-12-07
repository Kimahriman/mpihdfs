#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0
static const long LIMIT=1048576;

MPI_Offset write_file(char * name, long file_size, long block_size) {
	double start_write, end_write, total_time;
	long i;
	char *chunk;
	long written = 0;
	MPI_File out;

	MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_WRONLY, MPI_INFO_NULL, &out);

	chunk = malloc(block_size * sizeof(char));
	for (i=0; i < block_size; i++) {
		chunk[i] = (char)(i % 256);
	}

	start_write = MPI_Wtime();

	while (written < file_size) {
		MPI_File_write(out, chunk, block_size, MPI_CHAR, MPI_STATUS_IGNORE);
		written += block_size;
	}

	end_write = MPI_Wtime();
	total_time=end_write - start_write;
	
	printf("Time for whole write: %.2lf secs.\n", total_time);
	printf("Total size: %lu bytes.\n", (unsigned long)file_size);
	printf("Bandwidth: %.21f MB/s.\n", file_size / (1024*1024) / total_time);
	
	free(chunk);
	MPI_File_close(&out);
	return file_size;
}

int main(int argc, char * argv[]) {
	int size, rank; 
	long block_size, file_size;
	int namelen;
	double start=0.0, end;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);

	fprintf(stdout, "Process %d of %d is on %s\n",
			rank, size, processor_name);
	fflush(stdout);

	block_size = atol(argv[3]);
	file_size = atol(argv[2]);

	if (rank == MASTER)
		start=MPI_Wtime();
	
	//process_file(&in, size, rank, &out, argv[1], argv[2]);

	//if (rank == MASTER){
	//	end=MPI_Wtime();
	//	printf("Wallclock time elapsed: %.2lf seconds\n", end-start);
	//}

	file_size = write_file(argv[1], file_size, block_size);
	//write_file(size, rank, argv[2], file_size);
	if(rank==MASTER){
		end=MPI_Wtime();
		printf("Total wall clock time: %.21lf seconds.\n", end-start);
	}

	MPI_Finalize();
	return 0;

}
