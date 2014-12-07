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
 "" using 4 with linespoints lw 1.5 pt 5 ps 1.5 ti "ADAM",\
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
 "" using 3 with linespoints lw 1.5 pt 5 ps 1.5 ti "ADAM",\
 "" using 4:xtic(1) with linespoints lw 1.5 pt 4 ps 1.5 ti "FuseDFS" 

#reset
#set terminal postscript eps enhanced "Helvetica" 26 
#set nolog xy
#set key nobox out horiz center top
#set ytics 1000
#set boxwidth 0.3
#set size 1, 0.75
#set style fill solid border 1
#set ylabel "Average job execution time (s)"
#set output "mpi_vs_yarn_big.eps"
#set xr[0.5 : 6.5]
#set xtics("milc" 1, "GemsFDTD" 2, "pop2" 3, "lammps" 4, "socorro" 5, "lu" 6)
#set xtics nomirror rotate by -25 offset -1.5,0
#set yr [:5500]
#set grid y
#
#plot "mpi_vs_yarn_big.dat" using ($1-0.15):2 w boxes fs  pattern 1  title 'MPI', \
#""  using ($1+0.15):3 w boxes fs  solid 0.4  title 'Gerbil' 
#----------------------------------------------------------------------
