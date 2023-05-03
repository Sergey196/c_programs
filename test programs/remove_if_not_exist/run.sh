#!/bin/bash 

array1=($(ls -1 DIR1/))
array2=($(ls -1 DIR2/))

#for str in ${array1[@]}; do
#  echo $str
#done
#
#echo "///////////////////////////////////////////////////"
#
#for str in ${array2[@]}; do
#  echo $str
#done

for target in ${array2[@]}; do
  for i in ${!array1[@]}; do
    if [[ ${array1[i]} = $target ]]; then
      unset array1[i]
    fi
  done
done

echo "///////////////////////////////////////////////////"

for str in ${array1[@]}; do
  rm "DIR1/$str"
done

#lsblk /dev/sd[b-z][0-1] -ln -o MOUNTPOINT
#ls -1 /media/utkinsv/
