# Mandelbrot
This is a Mandelbrot viewer intended for exploring different segments of the Mandelbrot set.

## Installation
To install this viewer locally please use the makefile provided with the project:
```bash
$ make all
```
This will generate a `main.out` binary in `bin` that upon execution will begin traversing the Mandelbrot set.
Exploration is performed using the parameters provided [here](src/main.cpp) (near the top of main).
Users interested in exploring a new segment can change the `Mandelbrot` attributes assigned,
and recompile the application.

Here's a point of interest to get you started (source: http://paulbourke.net/fractals/mandelbrot/):
```cpp
fractals::mandelbrot::Mandelbrot mandelbrot = {
    -0.7746806106269039,
    -0.1374168856037867,
    40,
    2000,
    4,
    1440,
    900,
    {122, 66, 244, 255},
    {234, 115, 51, 255}
};
```

## Compiling to WASM
The makefile provided with the project includes a rule for building a Mandelbrot WASM web app.
Make sure that `emcc` is installed on the system, and then run the following:
```bash
$ make wasm
```
This will generate a `wasm-deploy` directory that will have everything needed for using the Mandelbrot HTML viewer.
**Note:** Due to CORS, assets application will need to be served over a web server.
A simple way to get around this for local testing is to run a Python HTTP server using:
```bash
$ python -m http.server --directory wasm-deploy
```
^ Where `python` is python version 3 and the command is executed from the root of the project directory.

## Public Resource
Users interested in exploring the Mandelbrot set from their browser that don't want to go through the installation instructions provided above can use the following [site](https://old-site.hamologist.com/mandelbrot). Note: This public resource is actually implemented in Javascript and the code for the JS implementation can be found [here](https://github.com/hamologist/hamologist-website/tree/master/components/demos/mandelbrot). The Mandelbrot computation happens in [this](https://github.com/hamologist/hamologist-website/blob/master/components/demos/mandelbrot/workers/mandelbrotCompute.ts) web worker.
