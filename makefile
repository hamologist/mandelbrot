CC := clang++
EMCC := emcc

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

CFLAGS := -std=c++11 -O3
EMCCFLAGS := -std=c++11 -O3
LIB := -lSDL2
INC := -I include

all: bin build bin/main.out

wasm: \
	wasm-deploy \
	build \
	wasm-deploy/mandelbrot.js

bin:
	mkdir -p bin

build:
	mkdir -p build

wasm-deploy:
	mkdir -p wasm-deploy

# Main Code 
bin/main.out: build/main.o build/mandelbrot.o
	$(CC) $(CFLAGS) build/mandelbrot.o build/main.o -o bin/main.out $(LIB)

build/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(INC) -c src/main.cpp -o build/main.o

build/mandelbrot.o: src/mandelbrot.cpp
	$(CC) $(CFLAGS) $(INC) -c src/mandelbrot.cpp -o build/mandelbrot.o

# wasm
wasm-deploy/mandelbrot.js: build/mandelbrot.bc build/mandelbrot_embind.bc
	$(EMCC) $(EMCCFLAGS) $(INC) \
		--bind -s WASM=1 \
		build/mandelbrot.bc \
		build/mandelbrot_embind.bc \
		-o wasm-deploy/mandelbrot.js

wasm-deploy/chip-eight-interface.js:
	cp wasm/chip-eight-interface.js wasm-deploy/chip-eight-interface.js

wasm-deploy/chip-eight.css:
	cp wasm/chip-eight.css wasm-deploy/chip-eight.css

wasm-deploy/index.html:
	cp wasm/index.html wasm-deploy/index.html

build/mandelbrot.bc: src/mandelbrot.cpp
	$(EMCC) $(EMCCFLAGS) $(INC) -c src/mandelbrot.cpp -o build/mandelbrot.bc

build/mandelbrot_embind.bc: src/mandelbrot_embind.cpp
	$(EMCC) $(EMCCFLAGS) $(INC) -c src/mandelbrot_embind.cpp -o build/mandelbrot_embind.bc

# Other
clean:
	rm -rf bin build

tags: src/* include/*
	$(CC) $(CFLAGS) $(INC) -M src/* | sed -e 's/[\\ ]/\n/g' | \
        sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' | \
        ctags -L - --c++-kinds=+p --fields=+iaS --extra=+q
