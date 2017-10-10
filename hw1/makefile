.PHONY: main clean run
main:hw1
hw1:dsahw1.o
	g++ dsahw1.o -o hw1
dsahw1.o:dsahw1.cpp
	g++ dsahw1.cpp -c
clean:
	rm -rf dsahw1.o
run:hw1
	./hw1