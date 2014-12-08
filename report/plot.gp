reset
set terminal postscript eps enhanced "Helvetica" 26
set nolog xy
set ylabel "Read Bandwidth (MB/s)"
set xlabel "Number of processes"
set output "read1.eps"
set key nobox out horiz center top
set boxwidth 0.6
set size 1,0.75
set yr[:26000]

set style fill solid border 1
#set xr [0.5 : 4.5]
set xtics nomirror 
set grid y

plot  \
 "read1.dat" using 2 with linespoints lw 1.5 pt 7 ps 1.5 ti "Local",\
 "" using 3 with linespoints lw 1.5 pt 6 ps 1.5 ti "NFS",\
 "" using 4 with linespoints lw 1.5 pt 5 ps 1.5 ti "MPIHDFS",\
 "" using 5:xtic(1) with linespoints lw 1.5 pt 4 ps 1.5 ti "FuseDFS" 


#----------------------------------------------------------------------
reset
set terminal postscript eps enhanced "Helvetica" 26
set nolog xy
set ylabel "Read Bandwidth (MB/s)"
set xlabel "Number of processes"
set output "read2.eps"
set key nobox out horiz center top
set boxwidth 0.6
set size 1,0.75
#set yr[:26000]

set style fill solid border 1
#set xr [0.5 : 4.5]
set xtics nomirror 
set grid y

plot  \
 "read2.dat" using 2 with linespoints lw 1.5 pt 6 ps 1.5 ti "NFS",\
 "" using 3 with linespoints lw 1.5 pt 5 ps 1.5 ti "MPIHDFS",\
 "" using 4:xtic(1) with linespoints lw 1.5 pt 4 ps 1.5 ti "FuseDFS" 

#----------------------------------------------------------------------
reset
set terminal postscript eps enhanced "Helvetica" 26
set nolog xy
set ylabel "Read Bandwidth (MB/s)"
set xlabel "Number of processes"
set output "read3.eps"
set key nobox out horiz center top
set boxwidth 0.6
set size 1,0.75
#set yr[:26000]

set style fill solid border 1
#set xr [0.5 : 4.5]
set xtics nomirror 
set grid y

plot  \
 "read3.dat" using 2 with linespoints lw 1.5 pt 6 ps 1.5 ti "NFS",\
 "" using 3 with linespoints lw 1.5 pt 5 ps 1.5 ti "MPIHDFS",\
 "" using 4:xtic(1) with linespoints lw 1.5 pt 4 ps 1.5 ti "FuseDFS" 
#----------------------------------------------------------------------
reset
set terminal postscript eps enhanced "Helvetica" 26
set nolog xy
set ylabel "Read Bandwidth (MB/s)"
set xlabel "Number of processes"
set output "read4.eps"
set key nobox out horiz center top
set boxwidth 0.6
set ytics 1000
set size 1,0.75
#set yr[:26000]

set style fill solid border 1
#set xr [0.5 : 4.5]
set xtics nomirror 
set grid y

plot  \
 "read4.dat" using 2 with linespoints lw 1.5 pt 5 ps 1.5 ti "MPIHDFS-3",\
 "" using 3:xtic(1) with linespoints lw 1.5 pt 4 ps 1.5 ti "FuseDFS-3" ,\
 "" using 4 with linespoints lw 1.5 pt 3 ps 1.5 ti "FuseDFS-1",\
 "" using 5 with linespoints lw 1.5 pt 2 ps 1.5 ti "MPIHDFS-1"

reset
set terminal postscript eps enhanced "Helvetica" 26 
set nolog xy
set nokey 
set style data histogram
set boxwidth 1.5
set size 1, 0.75
set ylabel "Write Bandwidth (MB/s)"
set output "write.eps"
set xtics nomirror rotate by -25 offset -1.5,0
set grid y

plot "write.dat" using 2:xticlabels(1) fs solid
#----------------------------------------------------------------------
reset
set terminal postscript eps enhanced "Helvetica" 26
set nolog xy
set ylabel "Read Overhead"
set xlabel "Number of processes"
set output "over1.eps"
set key nobox out horiz center top
#set ytics 1000
set size 1,0.75
set yr[0.4:1.6]

set style fill solid border 1
#set xr [0.5 : 4.5]
set xtics nomirror 
set grid y

plot  \
 "over.dat" using 2 with linespoints lw 1.5 pt 5 ps 1.5 ti "MPIHDFS",\
 "" using 3:xtic(1) with line ti "MPI-IO" 
