rm $1
g++-4.9 "$1.cpp" -o $1 --std=c++11
for i in {0..19}
do
    echo $i
    "./$1" < "tests/$i.in" > output.txt
    diff "tests/$i.out"  output.txt
done
