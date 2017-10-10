.PHONY: main clean run
main:2.2
2.2:2.2.o
	g++ 2.2.o -o 2.2 -O3
2.2.o:2.2.cpp
	g++ 2.2.cpp -c -O3
clean:
	rm -rf 2.2.o
run:2.2
	./2.2