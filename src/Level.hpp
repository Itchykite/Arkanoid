#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Brick.hpp"

class Ball;
class Player;

class Level 
{
private:
    std::vector<Brick> bricks;
    static int levelNumber;

public:
    Level();
    ~Level();

    void draw(SDL_Renderer* renderer) const;
    void reset(Ball*& ball);
    bool isComplete() const;
    void removeBrick(SDL_Rect ballRect, Ball*& ball, SDL_Rect playerRect, Player*& player);
    static int getLevelNumber() { return levelNumber; }
    static void setLevelNumber(int newLevel) { levelNumber = newLevel; }
};
