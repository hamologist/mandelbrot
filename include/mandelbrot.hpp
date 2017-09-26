#include <vector>
#include <cstdint>

namespace fractals {
    struct rgba {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    };

    namespace mandelbrot {
        struct Mandelbrot {
            double x_c;
            double y_c;
            double zoom;
            uint32_t max_iterations;
            uint32_t escape_point;
            uint32_t view_width;
            uint32_t view_height;
            rgba first_color;
            rgba second_color;
        };

        typedef std::vector<std::vector<rgba>> view_data;

        view_data compute(Mandelbrot);
    }
}
