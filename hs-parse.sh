#!/bin/sh

for i in `seq 1 5 46`; do
	sum=`grep ^Bandwidth hyogi-result.txt | tail -n+$i | head -n5 | awk '{print $2}' | paste -sd'+' | bc`
	avg=`echo "scale=3; $sum / 5.0" | bc`
	echo $avg
done

