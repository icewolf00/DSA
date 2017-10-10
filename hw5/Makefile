.PHONY: main clean run
main:hw5
hw5:hw5.o
	g++ hw5.o -o hw5 -O3
hw5.o:hw5.cpp
	g++ hw5.cpp -c -O3
clean:
	rm -rf hw5.o
run:hw5
	./hw5