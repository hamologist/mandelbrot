#include <mandelbrot.hpp>
#include <vector>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mandelbrot) {
    register_vector<fractals::rgba>("view_data_row");
    register_vector<std::vector<fractals::rgba>>("view_data");

    value_object<fractals::rgba>("rgba")
        .field("red", &fractals::rgba::red)
        .field("green", &fractals::rgba::green)
        .field("blue", &fractals::rgba::blue)
        .field("alpha", &fractals::rgba::alpha);

    value_object<fractals::mandelbrot::Mandelbrot>("Mandelbrot")
        .field("x_c", &fractals::mandelbrot::Mandelbrot::x_c)
        .field("y_c", &fractals::mandelbrot::Mandelbrot::y_c)
        .field("zoom", &fractals::mandelbrot::Mandelbrot::zoom)
        .field("max_iterations", &fractals::mandelbrot::Mandelbrot::max_iterations)
        .field("escape_point", &fractals::mandelbrot::Mandelbrot::escape_point)
        .field("view_width", &fractals::mandelbrot::Mandelbrot::view_width)
        .field("view_height", &fractals::mandelbrot::Mandelbrot::view_height)
        .field("first_color", &fractals::mandelbrot::Mandelbrot::first_color)
        .field("second_color", &fractals::mandelbrot::Mandelbrot::second_color);

    function("mandelbrot_compute", &fractals::mandelbrot::compute);
}
