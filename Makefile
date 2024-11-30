all: main

main: main.cc
	g++ -o main main.cc 

run: main
	./main test.pla

clean:
	rm main solution.pla