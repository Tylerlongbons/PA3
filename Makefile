#MakeFile for PA3
#Tyler Longbons

CC=g++
CFLAGS=-c -Wall -I.
OFLAGS=-o

pa3: main.o image.o
				$(CC) main.o image.o $(OFLAGS) pa3

main.o: main.cpp
				$(CC) $(CFLAGS) main.cpp

image.o: image.cpp image.h
				$(CC) $(CFLAGS) image.cpp

clean:
				rm -f *.o pa3

tar:
				tar cf PA3.tar *.cpp *.h Makefile																