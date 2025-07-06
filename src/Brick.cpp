#include "Brick.hpp"

Brick::Brick(int x, int y, int width, int height, Uint32 color)
    : rect{ x, y, width, height }, color(color) 
{
}

void Brick::draw(SDL_Renderer* renderer) const 
{
    SDL_SetRenderDrawColor(renderer, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 255);
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Brick::getRect() const 
{
    return rect;
}

Uint32 Brick::getColor() const 
{
    return color;
}
