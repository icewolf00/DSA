.PHONY: main clean run
main:hw3
hw3:hw3.o
	g++ hw3.o -o hw3 -O3
hw3.o:hw3.cpp
	g++ hw3.cpp -c -O3
clean:
	rm -rf hw3.o
run:hw3
	./hw3