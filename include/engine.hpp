#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "state.hpp"
#include "config.hpp"

class Engine
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_bool done;
    std::vector<SDL_FPoint> points;
    std::vector<SDL_Color> colors;
    SDL_Event event;
    State game_state;
    Config game_configuration;

    void drawpixel(double xm, double ym, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255);
    void clearpixels();
    void update();
    void input();
    void reset();

public:
    Engine();
    void Init(Config &configuration);
    void Loop();
};