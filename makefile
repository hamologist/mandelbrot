CC := clang++

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

CFLAGS := -std=c++11 -g
EMCCFLAGS := -std=c++11 -O3
LIB := -lSDL2
INC := -I include

all: bin build bin/main.out

bin:
	mkdir -p bin

build:
	mkdir -p build

# Main Code 
bin/main.out: build/main.o build/mandelbrot.o
	$(CC) $(CFLAGS) build/mandelbrot.o build/main.o -o bin/main.out $(LIB)

build/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(INC) -c src/main.cpp -o build/main.o

build/mandelbrot.o: src/mandelbrot.cpp
	$(CC) $(CFLAGS) $(INC) -c src/mandelbrot.cpp -o build/mandelbrot.o

# Other
clean:
	rm -rf bin build

tags: src/* include/*
	$(CC) $(CFLAGS) $(INC) -M src/* | sed -e 's/[\\ ]/\n/g' | \
        sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' | \
        ctags -L - --c++-kinds=+p --fields=+iaS --extra=+q
