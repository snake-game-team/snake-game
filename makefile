all : main

main : main.cpp *.h
	g++ -o main main.cpp -lncurses

clean:
	rm -f main