#ifndef MPIHOOK_H
#define MPIHOOK_H

#define _GNU_SOURCE

#include "hdfs.h"
#include "hdfs_url.h"
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
#define BUF_SIZE 4096

#define NOT_IMPLEMENTED { fprintf(stderr, "Function not implemented.\n"); return -1; }

typedef struct
{
	int32_t magic;
	hdfsFS fs;
	hdfsFile file;
	char *filename;
	int amode;
} hdfsFile_wrapper;

#endif
