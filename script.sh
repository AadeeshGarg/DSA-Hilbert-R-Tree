rm *.o
rm exe
gcc -c main.c
gcc -c functions.c
gcc -o exe main.o functions.o
./exe
rm *.o
rm exe
