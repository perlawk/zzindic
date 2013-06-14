all:
	gcc -o test test.c zigzag.c
	./test table.csv

clean:
	rm -f test *.o
