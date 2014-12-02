#ifndef OPTIONS_H
#define OPTIONS_H

/*
 * The DEFAULT option does not parse the file path passed to MPI functions,
 * and assumes all MPI file interactions are with the default HDFS running
 * on the machine.
 */
#define DEFAULT

/*
 * The NO_MPI option forces the hooking functions to not call any other MPI
 * functions. In order for calls to MPI functions to work, the MPI libraries
 * on the machine must be compiled as position-independent code. If they are
 * not, you can enable this option to prevent any MPI functions from being
 * called. This limits the functionality of the hooking library, such as
 * requiring all reads/writes be on bytes and not arbitrary datatypes.
 */
//#define NO_MPI

#endif
