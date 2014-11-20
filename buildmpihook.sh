#!/bin/sh

HDFS_INCLUDE=$HADOOP_HOME/include
HDFS_NATIVE=$HADOOP_HOME/lib/native
LIBJVM=$JAVA_HOME/jre/lib/amd64/server

mpicc hdfs_url.c MPIHook.c -I$HDFS_INCLUDE -L$HDFS_NATIVE -L$LIBJVM -lhdfs -ljvm -ldl -shared -fPIC -o MPIHook.so
