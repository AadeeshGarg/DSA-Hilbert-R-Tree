rm *.o
rm exe
gcc -c main.c
gcc -o exe main.o
./exe
rm *.o
rm exe