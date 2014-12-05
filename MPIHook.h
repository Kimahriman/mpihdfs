#ifndef MPIHOOK_H
#define MPIHOOK_H

#define _GNU_SOURCE

#include "hdfs.h"
#include "hdfs_url.h"
#include "options.h"
#include <mpi.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>

#ifdef DEBUG
#define status(str, ...) printf(str, ##__VA_ARGS__)
#else
#define status(str, ...)
#endif

#define HDFSFILEMAGIC 0x19d48be3

#ifdef CONST_BUF
#define MPIHDFS_CONST const
#else
#define MPIHDFS_CONST
#endif

#define NOT_IMPLEMENTED { fprintf(stderr, "Function not implemented.\n"); return -1; }

typedef struct
{
	int32_t magic;	// Indicates this is HDFS object
	hdfsFS fs;	// HDFS file system object
	hdfsFile file;	// HDFS file object
	char *filename; // Name of file in HDFS
	int mode;	// Mode for opening in HDFS
	int amode;	// Mode for opening in MPI
} hdfsFile_wrapper;

#endif
