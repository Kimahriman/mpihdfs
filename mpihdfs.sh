#!/bin/sh

HDFS_NATIVE=$HADOOP_HOME/lib/native
LIB_JVM=$JAVA_HOME/jre/lib/amd64/server
MPIHOOK_PATH=/home/xuluna/mpihdfs/MPIHook.so

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HDFS_NATIVE:$LIB_JVM
export LD_PRELOAD=$MPIHOOK_PATH

CLASSPATH=./

for file in `hadoop classpath | tr ':' ' ' | sort | uniq`
do
	CLASSPATH=$CLASSPATH:$file
done

for file in $HADOOP_HOME/*.jar
do
	CLASSPATH=$CLASSPATH:$file
done

for file in $HADOOP_HOME/lib/*.jar
do
	CLASSPATH=$CLASSPATH:$file
done

export CLASSPATH=$CLASSPATH


$@
