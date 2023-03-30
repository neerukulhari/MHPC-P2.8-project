../LJMD_serial/build/ljmd-serial.x < argon_108.inp
head -10 argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> a.dat
head -10 ../reference/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> b.dat
if cmp -s a.dat b.dat; then echo "The argon_108 simulation was executed without errors."; fi
rm -f a.dat b.dat