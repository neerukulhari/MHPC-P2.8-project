PROGRAM=$1
FILE_NAME=$2
# Run the test
$PROGRAM < $FILE_NAME.inp
head -10 $FILE_NAME.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> a.dat
head -10 ../reference/$FILE_NAME.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> b.dat
if cmp -s a.dat b.dat; then echo "The $FILE_NAME simulation was executed without errors."; fi
rm -f a.dat b.dat