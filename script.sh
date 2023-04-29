rm *.o
rm exe
gcc -c functions.c
gcc -c main.c
gcc -o exe functions.o main.o
./exe
rm *.o
rm exe