CC=mpicc
HDFS_INCLUDE=$(HADOOP_HOME)/include
HDFS_NATIVE=$(HADOOP_HOME)/lib/native
LIB_JVM=$(JAVA_HOME)/jre/lib/amd64/server

CFLAGS=-c -I$(HDFS_INCLUDE) -fPIC
LDFLAGS=-L$(HDFS_NATIVE) -L$(LIB_JVM) -lhdfs -ljvm -ldl -shared -fPIC
OBJS=hdfs_url.o MPIHook.o MPIFile.o MPISync.o

all: clean-main hook

debug: CFLAGS += -DDEBUG
debug: all

hook: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o MPIHook.so

%.o: %.c
	$(CC) $(CFLAGS) $<

test: clean-test MPITest.c
	$(CC) MPITest.c -o MPITest

clean-main:
	rm -f *.o MPIHook.so

clean-test:
	rm -f MPITest

clean: clean-main clean-test
