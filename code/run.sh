#!/bin/bash

path=/home/hx/Desktop/exp/instance/
mpath=/home/hx/Desktop/exp/minisat/core/minisat
out=/home/hx/Desktop/exp/out/
for file in `ls $path`
do
 result=`$mpath ${path}${file} ${out}${file}`
 time=`echo "$result" | grep 'CPU time'`
 time=`echo $time | awk -F: '{print $2}'`
 satisfiable=`echo "$result" | sed -n '$'p`
 echo "$file $satisfiable $time"
done
