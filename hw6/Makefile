.PHONY: main clean run
main:hw6
hw6:hw6.o
	g++ hw6.o -o hw6 -O3
hw6.o:hw6.cpp
	g++ hw6.cpp -c -O3
clean:
	rm -rf hw6.o
run:hw6
	./hw6