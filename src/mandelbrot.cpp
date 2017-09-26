#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>
#include <mandelbrot.h>

fractals::mandelbrot::view_data fractals::mandelbrot::compute(double center, double c, double zoom, uint32_t max_iterations, uint32_t break_point, uint16_t width, uint16_t height) {
    double x_min = -2.0 / zoom;
    double y_min = -1.0 / zoom;
    double x_max = 1.0 / zoom;
    double y_max = 1.0 / zoom;
    double x_dist = x_max - x_min;
    double y_dist = y_max - y_min;
    double x_cord, y_cord, x, y, x_temp;
    uint32_t iteration;
    uint8_t color;

    if (max_iterations == 0) {
        return view_data(0);
    }

    view_data current_view_data(height);

    for (uint16_t p_y = 1; p_y <= height; p_y++) {
        auto y_view = current_view_data[p_y - 1];
        y_cord = (y_dist * (p_y/(double)height)) + y_min;

        for (uint16_t p_x = 1; p_x <= width; p_x++) {
            x_cord = (x_dist * (p_x/(double)width)) + x_min;
            x = 0;
            y = 0;
            iteration = 0;
            
            while (x*x + y*y < break_point && iteration < max_iterations) {
                x_temp = x*x - y*y + x_cord;
                y = 2*x*y + y_cord;
                x = x_temp;
                iteration++;
            }

            double intensity = iteration / (double)max_iterations;
            rgba current_rgba  = {255, 255, 255, 255};

            if (iteration == max_iterations) {
                current_rgba.red = 0;
                current_rgba.green = 0;
                current_rgba.blue = 0;
            } else if (intensity < 0.25) {
                current_rgba.red = 0;
                current_rgba.green = 255.0 - (1020.0 * (intensity - 0.75));
            } else if (intensity < 0.5) {
                current_rgba.red = 0;
                current_rgba.blue = 255.0 * (1020.0 * (intensity - 0.50));
            } else if (intensity < 0.75) {
                current_rgba.red = 255.0 - (1020.0 * (intensity - 0.25));
                current_rgba.blue = 0;
            } else {
                current_rgba.green = 1020.0 * intensity;
                current_rgba.blue = 0;
            }
            
            y_view.push_back(current_rgba);
        }
        current_view_data[p_y - 1] = y_view;
    }

    return current_view_data;
}
