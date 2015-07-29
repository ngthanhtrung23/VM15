for i in {0..19}
do
    echo "$i"
    ./validator < "tests/$i.in"
done
