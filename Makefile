

all: test

test: test.o resources.o
	gcc test.o resources.o -o Win32APItest.exe

test.o: test.c
	gcc -c test.c -o test.o -I.

resources.o: test.rc
	windres test.rc -o resources.o

clean:
	rm -f Win32APItest.exe
	rm -f *.o
