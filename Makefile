CC=mpicc
HDFS_INCLUDE=$(HADOOP_HOME)/include
HDFS_NATIVE=$(HADOOP_HOME)/lib/native
LIB_JVM=$(JAVA_HOME)/jre/lib/amd64/server

CFLAGS=-c -I$(HDFS_INCLUDE) -fPIC
LDFLAGS=-L$(HDFS_NATIVE) -L$(LIB_JVM) -lhdfs -ljvm -ldl -shared -fPIC
OBJS=hdfs_url.o MPIHook.o MPIFile.o MPISync.o

all: clean hook test bench

debug: CFLAGS += -DDEBUG
debug: all

hook: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o libmpihdfs.so

%.o: %.c
	$(CC) $(CFLAGS) $<

test: clean-test MPITest.c
	$(CC) MPITest.c -o MPITest

bench: clean-bench bench.c writebench.c
	$(CC) bench.c -o bench
	$(CC) writebench.c -o writebench


clean-main:
	rm -f *.o MPIHook.so

clean-test:
	rm -f MPITest

clean-bench:
	rm -f bench writebench

clean: clean-main clean-test clean-bench
