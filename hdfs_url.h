#ifndef HDFS_URL_H
#define HDFS_URL_H

int hdfs_url_parse(const char *filename, char *hdfs_fsname, int fsname_buf_len, 
			  char *hdfs_filename, int filename_buf_len);

#endif
