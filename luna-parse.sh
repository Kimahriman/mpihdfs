#!/bin/sh

	sum=`grep ^Bandwidth hyogi-result.txt | head -n5 | awk '{print $2}' | paste -sd'+' | bc`
	avg=`echo "scale=3; $sum / 5.0" | bc`
	echo $avg

