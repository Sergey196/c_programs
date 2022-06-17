#!/bin/bash 

values=()
fileOldState="./file.txt"

while IFS= read -r line
do
  values+=("$line")
done < fileOldState

values[0]=Hello
echo ${values[0]}

truncate -s 0 $fileOldState

for i in "${values[@]}"
do
	echo $i >> $fileOldState
done

a=2
b=2

if [ -n $a ] && [ $a == $b ]
then
   echo "TEST"
fi
