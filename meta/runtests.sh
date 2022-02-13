FAILURES=0
for liz_file in `ls test/syntax/**/*.liz test/syntax/*.liz`;
do  
    echo $liz_file;
    echo "-------"
    build/liz $liz_file || FAILURES=$(($FAILURES+1));
    echo "-------"
done;
echo $FAILURES;