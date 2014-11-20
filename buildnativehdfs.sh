#!/bin/sh

mpicc -shared -ldl -fPIC $1 -I$HADOOP_HOME/include -L$HADOOP_HOME/lib/native -L$JAVA_HOME/jre/lib/amd64/server -lhdfs -ljvm -o $2
