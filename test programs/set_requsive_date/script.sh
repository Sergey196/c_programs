touch -t $2 $1

for f in $(find $1); do echo $f; done

for f in $(find $1); do touch -t $2 $f; done

#./script.sh test 1212031429.30
# 2012.12.03 14-29-30
