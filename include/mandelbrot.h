#include <vector>
#include <cstdint>

namespace fractals {
    struct rgba {
        uint8_t red;
        uint8_t blue;
        uint8_t green;
        uint8_t alpha;
    };

    namespace mandelbrot {
        typedef std::vector<std::vector<rgba>> view_data;
        view_data compute(double center, double c, double zoom, uint32_t max_iterations, uint32_t break_point, uint16_t width, uint16_t height);
    }
}
