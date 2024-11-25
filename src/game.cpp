#include "../include/engine.hpp"
#include "../include/config.hpp"

const int GAME_WIDTH = 200;
const int GAME_HEIGHT = 100;

int main()
{
    Config configuration { "config.json" };
    Engine gameoflife { };
    gameoflife.Init(configuration);
    gameoflife.Loop();
}