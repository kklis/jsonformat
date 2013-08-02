all:
	gcc -Wall -O2 -s -o jsonformat jsonformat.c
clean:
	rm -rf jsonformat jsonformat.exe
