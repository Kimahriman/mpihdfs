#define _GNU_SOURCE

#include "hdfs.h"
#include "hdfs_url.h"
#include <mpi.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int hdfs_url_parse(const char *filename, char *hdfs_fsname, int fsname_buf_len, 
			  char *hdfs_filename, int filename_buf_len)
{
	int len, i, ret;
	char *tmp;
	char prot[100];
	char host[1000];
	int port;
	char port_str[100];
	char path[1000];

	len = strlen(filename);

	tmp = malloc(len + 1);
	strcpy(tmp, filename);

	for (i=0; i < len; i++) {
		if (tmp[i] == ':')
			tmp[i] = ' ';
	}

	ret = sscanf(tmp, "%99s //%999s %d%999s[^\n]", prot, host, &port, path);

	if (ret < 4)
		return -1;

	if (strcmp(prot, "hdfs"))
		return -1;

	// Reconstruct the HDFS file system name
	strcpy(hdfs_fsname, prot);//, fsname_buf_len);
	strcat(hdfs_fsname, "://");//, fsname_buf_len);
	strcat(hdfs_fsname, host);//, fsname_buf_len);
	strcat(hdfs_fsname, ":");//, fsname_buf_len);
	
	printf("%d\n", port);
	sprintf(port_str, "%d", port);

	strcat(hdfs_fsname, port_str);//, fsname_buf_len);

	strcpy(hdfs_filename, path);//, filename_buf_len);

	return 0;
}
