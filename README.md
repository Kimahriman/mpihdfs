mpihdfs
=======

mpihdfs allows MPI applications to interact with an HDFS file system. mpihdfs works by wrapping all MPI I/O function calls to modify their behavior. The HDFS native library is used to provide access to a running HDFS file system. See report/report.pdf for more details on this project.

Building mpihdfs
====================

mpihdfs was built to be compatible with MPICH version 3.1. For use in other implementations, some modifications to the Makefile and or source files may be required.

In order to build mpihdfs, three variables in the Makefile must be set correctly. These are HDFS_INCLUDE, HDFS_NATIVE, and LIB_JVM. HDFS_INCLUDE must be set to the directory containing the header file "hdfs.h". This is typically found at $HADOOP_HOME/include, and should be included with Hadoop releases. HDFS_NATIVE must be set to the directory containing the library "libhdfs.so". This is typically found at $HADOOP_HOME/lib/native, and should also be included with Hadoop releases. Finally, LIB_JVM must be set to the directory containing the library "libjvm.so", which should be included with Java relases. This is typically found at $JAVA_HOME/jre/lib/<architecture>/(client|server).

With these variables set correctly, the project should now build successfully. If it does not, see the following options as they may be able to solve the issues.

Build Options for mpihdfs
=========================

There are a few build options available for mpihdfs. These options are selected by including various preprocessor definitions, and are available in the "options.h" file for easy toggling.

ALL_HDFS specifies that all MPI I/O operations should be assumed to want to use HDFS. Without this option turned in, files must be specified in the format "hdfs://<host of namenode>:<port><file path>" in order for MPI functions to interact with HDFS. If file paths are not in this format, then the wrapper functions pass control to the actual MPI functions to behave normally. If the ALL_HDFS option is turned on, then any file path is assumed to refer to the default HDFS location of the local computer, and the "hdfs://<host of namenode>:<port> need not and should not be included as part of the file path.

NO_MPI tells mpihdfs to not use any MPI functions as part of its own implementation. This was included to debug some issues, and should likely not be used. If mpihdfs will not build without including this option, it is unlikely mpihdfs will work as intended.

CONST_BUF changes all function prototypes of write functions to use const buffers instead of non-const buffers. Various versions and releases of MPICH seem to conflict on whether const buffers are used, so this is included to allow easy compilation for either variety. If there are build errors indicating a function is already defined, it is likely this option needs to be toggled for a successful build.

Running mpihdfs
===============

Like building mpihdfs, running mpihdfs requires setting a few variables in the script mpihdfs.sh. Two of these are the same as in the Makefile, HDFS_NATIVE and LIB_JVM. The final one, MPIHOOK_PATH, must be set to the full path of the location of the library built in the project, MPIHook.so.

After these are correctly set, mpihdfs is invoked by simply running the script mpihdfs.sh and passing as arguments the regular mpiexec or mpirun command you want to run. The script correctly sets the environment needed for mpihdfs to function correctly and then executes the command you give it.
