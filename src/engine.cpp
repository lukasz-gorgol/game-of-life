#include <SDL2/SDL.h>
#include <vector>

#include <cstdlib>
#include <tuple>
#include <iostream>
#include <time.h>
#include <algorithm>

#include "../include/engine.hpp"

Engine::Engine()
{
}

void Engine::Init(Config &configuration)
{
    game_configuration = configuration;
    game_state.width = game_configuration.getWindowWidth();
    game_state.height = game_configuration.getWindowHeight();
    game_state.scale = game_configuration.getWindowScale();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(
        game_state.width * game_state.scale,
        game_state.height * game_state.scale,
        SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer);
    SDL_RenderSetScale(
        renderer,
        game_state.scale,
        game_state.scale);
    game_state.display = new int *[game_state.height];
    game_state.swap = new int *[game_state.height];
    for (int row = 0; row < game_state.height; ++row)
    {
        game_state.display[row] = new int[game_state.width];
        game_state.swap[row] = new int[game_state.width];
    }
    srand(time(NULL));
    reset();
}

void Engine::reset()
{
    const int birthRate = game_configuration.getBirthRate();
    for (int row = 0; row < game_state.height; ++row)
    {
        for (int col = 0; col < game_state.width; ++col)
        {
            game_state.display[row][col] = rand() % birthRate % 2;
            game_state.swap[row][col] = 0;
        }
    }
    game_state.Restart = false;
}

void Engine::Loop()
{
    const int frame_time_limit = 1000 / game_configuration.getFPSLimit();
    while (game_state.Quit == false)
    {
        Uint32 frame_start = SDL_GetTicks();
        if (game_state.Restart == true)
            reset();
        for (int row = 0; row < game_state.height; ++row)
            for (int col = 0; col < game_state.width; ++col)
                game_state.swap[row][col] = game_state.isAlive(row, col) ? 1 : 0;
        for (int row = 0; row < game_state.height; ++row)
            for (int col = 0; col < game_state.width; ++col)
                if (game_state.Conway && game_state.swap[row][col])
                    drawpixel(row, col);
        int **swap_tmp = game_state.swap;
        game_state.swap = game_state.display;
        game_state.display = swap_tmp;
        update();
        input();
        Uint32 frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < frame_time_limit)
            SDL_Delay(frame_time_limit - frame_time);
        clearpixels();
    }
}

void Engine::drawpixel(double row, double col, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    points.emplace_back(col, row);
    colors.emplace_back(r, g, b, a);
}

void Engine::clearpixels()
{
    points.clear();
}

void Engine::update()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    if (game_state.Grid)
    {
        const int GRID_SPACING = 4;
        const SDL_Color GRID_COLOR = {0, 30, 0, 5};
        SDL_SetRenderDrawColor(renderer, GRID_COLOR.r, GRID_COLOR.g, GRID_COLOR.b, GRID_COLOR.a);
        for (int x = 0; x < game_state.width; x += GRID_SPACING)
        {
            SDL_RenderDrawLine(renderer, x, 0, x, game_state.height - 1);
        }
        for (int y = 0; y < game_state.height; y += GRID_SPACING)
        {
            SDL_RenderDrawLine(renderer, 0, y, game_state.width - 1, y);
        }
    }

    for (long unsigned int i = 0; i < points.size(); i++)
    {
        SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
        SDL_RenderDrawPointF(renderer, points[i].x, points[i].y);
    }

    SDL_RenderPresent(renderer);
}

void Engine::input()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_Quit();
            exit(0);
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_c:
                game_state.Conway = !game_state.Conway;
                break;
            case SDLK_g:
                game_state.Grid = !game_state.Grid;
                break;
            case SDLK_q:
                game_state.Quit = true;
                break;
            case SDLK_r:
                game_state.Restart = true;
                break;
            }
            break;
        }
    }
}
