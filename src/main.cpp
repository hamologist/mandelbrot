#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>
#include <mandelbrot.h>

int main() {
    bool running = true;
    uint16_t window_width = 1440;
    uint16_t window_height = 900;
    uint32_t max_iterations = 1000;
    uint32_t break_point = 4;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect pixel;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Mandelbrot",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_width,
        window_height,
        SDL_WINDOW_RESIZABLE
    );
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    pixel.w = 1;
    pixel.h = 1;

    auto view_data = fractals::mandelbrot::compute(0, 0, 1, max_iterations, break_point, window_width, window_height);
    for (uint16_t y = 0; y < view_data.size(); y++) {
        auto y_data = view_data[y];
        pixel.y = y;
        for (uint16_t x = 0; x < y_data.size(); x++) {
            auto x_data = y_data[x];
            SDL_SetRenderDrawColor(renderer, x_data.red, x_data.green, x_data.blue, 255);
            pixel.x = x;

            SDL_RenderFillRect(renderer, &pixel);
        }
    }
    SDL_RenderPresent(renderer);

    while(running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
            }
        }
        SDL_Delay(100);
    }

    return 0;
}
