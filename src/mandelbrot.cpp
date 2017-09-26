#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
#include <mandelbrot.hpp>

const static double DEFAULT_X_DISTANCE = 3.0;
const static double DEFAULT_Y_DISTANCE = 2.0;

fractals::mandelbrot::view_data fractals::mandelbrot::compute(fractals::mandelbrot::Mandelbrot mandelbrot) {
    long double x_dist = DEFAULT_X_DISTANCE / mandelbrot.zoom;
    long double y_dist = DEFAULT_Y_DISTANCE / mandelbrot.zoom;
    long double x_space = x_dist / 2.0;
    long double y_space = y_dist / 2.0;
    long double x_min = mandelbrot.x_c - x_space;
    long double y_min = mandelbrot.y_c - y_space;
    long double x_cord, y_cord, x, y, x_temp;
    uint32_t iteration;
    uint8_t color;
    uint8_t red_dis = abs(mandelbrot.first_color.red - mandelbrot.second_color.red);
    uint8_t green_dis = abs(mandelbrot.first_color.green - mandelbrot.second_color.green);
    uint8_t blue_dis = abs(mandelbrot.first_color.blue - mandelbrot.second_color.blue);
    uint8_t red_t = mandelbrot.first_color.red > mandelbrot.second_color.red ? 1 : -1;
    uint8_t green_t = mandelbrot.first_color.green > mandelbrot.second_color.green ? 1 : -1;
    uint8_t blue_t = mandelbrot.first_color.blue > mandelbrot.second_color.blue ? 1 : -1;

    if (mandelbrot.max_iterations == 0) {
        return view_data(0);
    }

    view_data current_view_data(mandelbrot.view_height);

    for (uint16_t p_y = 1; p_y <= mandelbrot.view_height; p_y++) {
        auto y_view = current_view_data[p_y - 1];
        y_cord = (y_dist * (p_y/(long double)mandelbrot.view_height)) + y_min;

        for (uint16_t p_x = 1; p_x <= mandelbrot.view_width; p_x++) {
            x_cord = (x_dist * (p_x/(long double)mandelbrot.view_width)) + x_min;
            x = 0;
            y = 0;
            iteration = 0;
            
            while (x*x + y*y < mandelbrot.escape_point && iteration < mandelbrot.max_iterations) {
                x_temp = x*x - y*y + x_cord;
                y = 2*x*y + y_cord;
                x = x_temp;
                iteration++;
            }

            rgba current_rgba;

            if (iteration == mandelbrot.max_iterations) {
                current_rgba = {0, 0, 0, 255};
            } else {
                long double intensity = iteration / (long double)mandelbrot.max_iterations;

                current_rgba.red = (uint8_t)(red_t * red_dis * intensity) + mandelbrot.first_color.red;
                current_rgba.green = (uint8_t)(green_t * green_dis * intensity) + mandelbrot.first_color.green;
                current_rgba.blue = (uint8_t)(blue_t * blue_dis * intensity) + mandelbrot.first_color.blue;
                current_rgba.alpha = 255;
            }

            y_view.push_back(current_rgba);
        }
        current_view_data[p_y - 1] = y_view;
    }

    return current_view_data;
}
