#include "../include/engine.hpp"
#include "../include/config.hpp"

int main()
{
    Config configuration { "config.json" };
    Engine gameoflife { };
    gameoflife.Init(configuration);
    gameoflife.Loop();
}