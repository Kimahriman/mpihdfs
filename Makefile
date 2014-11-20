CC=mpicc
HDFS_INCLUDE=$(HADOOP_HOME)/include
HDFS_NATIVE=$(HADOOP_HOME)/lib/native
LIB_JVM=$(JAVA_HOME)/jre/lib/amd64/server

CFLAGS=-c -I$(HDFS_INCLUDE) -fPIC
LDFLAGS=-L$(HDFS_NATIVE) -L$(LIB_JVM) -lhdfs -ljvm -ldl -shared -fPIC

all: hook

hook: hdfs_url.o MPIHook.o
	$(CC) $(LDFLAGS) hdfs_url.o MPIHook.o -o MPIHook.so

hdfs_url.o:
	$(CC) $(CFLAGS) hdfs_url.c

MPIHook.o:
	$(CC) $(CFLAGS) MPIHook.c

clean:
	rm -rf *.o MPIHook.so
