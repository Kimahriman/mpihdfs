#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0
static const long LIMIT=1024000;


MPI_Offset read_file(const int size, const int rank, char * name) {
	int err, i;
	double start_read, min_start_read, end_read, max_end_read, read=0, max_r, total_time;
	char *chunk;
	MPI_Offset file_size;
	MPI_File in;

	MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_RDONLY, MPI_INFO_NULL, &in);
	err = MPI_File_get_size(in, &file_size);

	if(err != 0){
		printf("Error: file open. code: %d. \n", err);
		MPI_Finalize();
		exit(1);
	}

	chunk = malloc(LIMIT * sizeof(char));

	MPI_Barrier(MPI_COMM_WORLD);

	start_read = MPI_Wtime();

	for(i = rank; i < file_size/LIMIT; i += size){
		MPI_File_read_at(in, i * LIMIT, chunk, LIMIT, MPI_CHAR, MPI_STATUS_IGNORE);
	}

	end_read = MPI_Wtime();
	
	MPI_Reduce(&start_read, &min_start_read, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce(&end_read, &max_end_read, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == MASTER) {
		total_time = max_end_read - min_start_read;
		printf("Time for whole read: %.2lf secs.\n", total_time);
		printf("Total size: %lu bytes.\n", file_size);
		printf("Bandwidth: %.21f MB/s.\n", file_size / (1024*1024) / total_time);
	}
	free(chunk);
	MPI_File_close(&in);
	return file_size;
}

int main(int argc, char * argv[]) {
	int size, rank;
	int namelen;
	double start, end;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Offset file_size;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);

	fprintf(stdout, "Process %d of %d is on %s\n",
			rank, size, processor_name);
	fflush(stdout);

	//if (rank == MASTER)
	//	start=MPI_Wtime();
	
	//process_file(&in, size, rank, &out, argv[1], argv[2]);

	//if (rank == MASTER){
	//	end=MPI_Wtime();
	//	printf("Wallclock time elapsed: %.2lf seconds\n", end-start);
	//}

	//file_size = read_file(size, rank, argv[1]);
	//write_file(size, rank, argv[2], file_size);
	//if(rank==MASTER){
	//	end=MPI_Wtime();
	//	printf("Total wall clock time: %.21lf seconds.\n", end-start);
	//}

	MPI_File in, out;
	int err, len;
	char buf[4096];

	printf("MPI_SUCCESS: %d\n", MPI_SUCCESS);

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
	printf("Total size: %lu bytes.\n", file_size);
	
	if (file_size < sizeof(buf)) {
		err = MPI_File_read(in, buf, file_size, MPI_CHAR, NULL);
		if (err == -1) {
			printf("Error: file read. code: %d. \n", err);
			MPI_Finalize();
			exit(-1);
		}
		buf[file_size] = 0;
		puts(buf);
	}

	err = MPI_File_write(out, buf, file_size, MPI_CHAR, NULL);
	if (err == -1) {
		printf("Error: file write. code: %d. \n", err);
		MPI_Finalize();
		exit(-1);
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
