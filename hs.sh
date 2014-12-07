#!/bin/sh
# ./mpihdfs.sh mpiexec -n 1 -hosts n165,ib166 ./bench hdfs://n165:9099/onegig 64000000

file="hyogi-result.txt"

for i in `seq 10`; do
	for try in `seq 5`; do
		echo | tee -a $file
		echo "# n=$i, try=$try" | tee -a $file
		echo "# command: ./mpihdfs.sh mpiexec -n $i -hosts n165,ib166 ./bench /mnt/hdfs/onegig 64000000" | tee -a $file
		./mpihdfs.sh mpiexec -n $i -hosts n165,ib166 ./bench hdfs://n165:9099/onegig 64000000 | tee -a $file
	done
done

