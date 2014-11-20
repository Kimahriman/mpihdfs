HDFS_NATIVE=$HADOOP_HOME/lib/native
LIBJVM=$JAVA_HOME/jre/lib/amd64/server
MPIHOOK_PATH=/usr/local/hadoop/native/MPIHook.so

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HDFS_NATIVE:$LIBJVM
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
