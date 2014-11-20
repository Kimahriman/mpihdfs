#include "hdfs.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MASTER 0
static const long LIMIT=1024 * 1024;

tOffset read_file(const int size, const int rank, char * name, hdfsFS fs) {
	int err, i;
	double start_read, min_start_read, end_read, max_end_read, read=0, max_r, total_time;
	char *chunk;
	tOffset file_size;
	
	hdfsFile readFile = hdfsOpenFile(fs, name, O_RDONLY, 0, 0, 0);
	if (!readFile) {
		fprintf(stderr, "Failed to open %s for writing!\n", name);
		MPI_Finalize();		
		exit(-1);
	}

	hdfsFileInfo *fileInfo = hdfsGetPathInfo(fs, name);
	
	file_size = fileInfo->mSize;
	printf("File size is %d\n", file_size);

	hdfsFreeFileInfo(fileInfo, 1);


	chunk = malloc(LIMIT * sizeof(char));

	MPI_Barrier(MPI_COMM_WORLD);

	start_read = MPI_Wtime();

	for(i = rank; i < file_size/LIMIT; i += size){
		//MPI_File_read_at(in, i * LIMIT, chunk, LIMIT, MPI_CHAR, MPI_STATUS_IGNORE);
		hdfsPread(fs, readFile, i * LIMIT, chunk, LIMIT);		
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
	return file_size;
}

void write_file(const int size, const int rank, char * name, tOffset file_size, hdfsFS fs) {
	int err, i;
	double start_write, min_start_write, end_write, max_end_write, total_time;
	char *chunk;
	MPI_File out;

	hdfsFile writeFile = hdfsOpenFile(fs, name, O_WRONLY | O_CREAT, 0, 0, 0);
	if (!writeFile) {
		fprintf(stderr, "Failed to open %s for writing!\n", name);
		MPI_Finalize();		
		exit(-1);
	}

	chunk = malloc(LIMIT * sizeof(char));

	for (i = 0; i < LIMIT * sizeof(char); i++)
		chunk[i] = (char)((i + rank) % 256);

	MPI_Barrier(MPI_COMM_WORLD);

	start_write = MPI_Wtime();

	for (i = rank; i < file_size/LIMIT; i += size) {
		//MPI_File_write_at(out, i * LIMIT, chunk, LIMIT, MPI_CHAR, MPI_STATUS_IGNORE);
		printf("Writing chunk %d\n", i);
		tSize num_written_bytes = hdfsWrite(fs, writeFile, chunk, LIMIT);
		if (hdfsFlush(fs, writeFile)) {
			fprintf(stderr, "Failed to 'flush' %s\n", name);
			exit(-1);
		}
			
	}

	end_write = MPI_Wtime();

	MPI_Reduce(&start_write, &min_start_write, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce(&end_write, &max_end_write, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	hdfsCloseFile(fs, writeFile);

	hdfsFileInfo *fileInfo = hdfsGetPathInfo(fs, name);
	tOffset new_file_size = fileInfo->mSize;
	hdfsFreeFileInfo(fileInfo, 1);

	if (rank == MASTER) {
		total_time = max_end_write - min_start_write;
		printf("Time for whole write: %.21f seconds.\n", total_time);
		printf("Total size: %lu bytes.\n", new_file_size);
		printf("Bandwidth: %.21f MB/s.\n", new_file_size / (1024*1024) / total_time);
	}

	free(chunk);
}


int main(int argc, char **argv) {
	struct hdfsBuilder *builder;
	int size, rank;
	int namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	if (argc < 3) {
		printf("Usage: hdfstest <file to read from> <file to write to>\n");
		exit(-1);
	}

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name, &namelen);

	fprintf(stdout, "Process %d of %d is on %s\n",
			rank, size, processor_name);
	fflush(stdout);

	builder = hdfsNewBuilder();

	hdfsBuilderSetNameNode(builder, "hdfs://localhost:9000");

	hdfsFS fs = hdfsBuilderConnect(builder);
	if (!fs) {
		fprintf(stderr, "Failed to connect to file system\n");
		exit(-1);
	}
	
	tOffset file_size = read_file(size, rank, argv[1], fs);
	write_file(size, rank, argv[2], file_size, fs);

	hdfsDisconnect(fs);
	MPI_Finalize();
}
