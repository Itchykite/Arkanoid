#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Brick.hpp"

class Ball;

class Level 
{
private:
    std::vector<Brick> bricks;

public:
    Level(int levelNumber);
    ~Level();

    void draw(SDL_Renderer* renderer) const;
    void reset(Ball*& ball);
    bool isComplete() const;
    void removeBrick(SDL_Rect ballRect, Ball*& ball, SDL_Rect playerRect);
};
