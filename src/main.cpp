#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>
#include <mandelbrot.hpp>

int main() {
    bool running = true;
    fractals::mandelbrot::Mandelbrot mandelbrot = {
        -1.7497219297423385717104386951868287166821567562234308144552652007051737509332,
        -0.0000290166477536876274764422704374969315895481370276256407423549503316886795,
        1,
        1000,
        4,
        1440,
        900,
        {122, 66, 244, 255},
        {234, 115, 51, 255}
    };
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect pixel;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Mandelbrot",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        mandelbrot.view_width,
        mandelbrot.view_height,
        SDL_WINDOW_RESIZABLE
    );
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    pixel.w = 1;
    pixel.h = 1;

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

        auto view_data = fractals::mandelbrot::compute(mandelbrot);
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
        mandelbrot.zoom *= 1.75;

        //SDL_Delay(1000);
    }

    return 0;
}
