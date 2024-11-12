all: main run

main: main.cc
	g++ -o main main.cc 

run: main
	./main

clean:
	rm main