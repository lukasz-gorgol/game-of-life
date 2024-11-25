#pragma once

#include <array>

class State
{
public:
    bool Restart = true;
    bool Quit = false;
    bool Conway = true;
    bool Grid = true;

    int **display;
    int **swap;

    int width;
    int height;
    float scale;

    bool isAlive(const int row, const int col)
    {
        int alive = 0;

        if (row > 0 && display[row - 1][col] == 1)
            alive += 1;
        if (row < height - 1 && display[row + 1][col] == 1)
            alive += 1;
        if (col > 0 && display[row][col - 1] == 1)
            alive += 1;
        if (col < width - 1 && display[row][col + 1] == 1)
            alive += 1;

        if (row > 0 && col > 0 && display[row - 1][col - 1] == 1)
            alive += 1;
        if (col > 0 && row < height - 1 && display[row + 1][col - 1] == 1)
            alive += 1;
        if (col < width - 1 && row > 0 && display[row - 1][col + 1] == 1)
            alive += 1;
        if (col < width - 1 && row < height - 1 && display[row + 1][col + 1] == 1)
            alive += 1;

        if (display[row][col] == 1 && alive < 2)
            return false;
        if (display[row][col] == 1 && (alive == 2 || alive == 3))
            return true;
        if (alive > 3)
            return false;
        if (display[row][col] == 0 && alive == 3)
            return true;

        return false;
    }
};