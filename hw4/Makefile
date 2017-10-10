.PHONY: main clean run
main:hw4
hw4:hw4.o
	g++ hw4.o -o hw4 -O3
hw4.o:hw4.cpp
	g++ hw4.cpp -c -O3
clean:
	rm -rf hw4.o
run:hw4
	./hw4