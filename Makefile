CC=mpicc
HDFS_INCLUDE=$(HADOOP_HOME)/include
HDFS_NATIVE=$(HADOOP_HOME)/lib/native
LIB_JVM=$(JAVA_HOME)/jre/lib/amd64/server

CFLAGS=-c -I$(HDFS_INCLUDE) -fPIC
LDFLAGS=-L$(HDFS_NATIVE) -L$(LIB_JVM) -lhdfs -ljvm -ldl -shared -fPIC

all: hook

debug: CFLAGS += -DDEBUG
debug: hook

hook: hdfs_url.o MPIHook.o MPIFile.o MPISync.o
	$(CC) $(LDFLAGS) hdfs_url.o MPIHook.o MPIFile.o MPISync.o -o MPIHook.so

%.o:
	$(CC) $(CFLAGS) $*.c

test:
	$(CC) MPITest.c -o MPITest

clean:
	rm -rf *.o MPIHook.so MPITest
