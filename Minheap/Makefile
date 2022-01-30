all: doublet

doublet: doublet.cpp MinHeap.h
	g++ -g -Wall -std=c++11 doublet.cpp -o doublet
	valgrind --leak-check=yes ./doublet

.PHONY: clean

clean:
	rm -f doublet

