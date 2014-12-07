#ifndef OPTIONS_H
#define OPTIONS_H

/*
 * The ALL_HDFS option does not parse the file path passed to MPI functions,
 * and assumes all MPI file interactions are with the default HDFS running
 * on the machine.
 */
//#define ALL_HDFS

/*
 * The NO_MPI option forces the hooking functions to not call any other MPI
 * functions. In order for calls to MPI functions to work, the MPI libraries
 * on the machine must be compiled as position-independent code. If they are
 * not, you can enable this option to prevent any MPI functions from being
 * called. This limits the functionality of the hooking library, such as
 * requiring all reads/writes be on bytes and not arbitrary datatypes.
 */
//#define NO_MPI

/*
 * Depending on the MPICH version, the MPI function prototypes may or may
 * not use const data buffers. If it does not compile due to conflicting
 * declaration of files, try turning this option on or off.
 */
#define CONST_BUF

#endif
