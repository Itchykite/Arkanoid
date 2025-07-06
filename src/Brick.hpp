#pragma once
#include <SDL2/SDL.h>

class Brick 
{
private:
    SDL_Rect rect;
    Uint32 color;

public:
    Brick(int x, int y, int width, int height, Uint32 color);

    void draw(SDL_Renderer* renderer) const; 

    SDL_Rect getRect() const; 
    Uint32 getColor() const;
};
