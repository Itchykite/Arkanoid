#pragma once

#include <SDL2/SDL2_gfxPrimitives.h>

class Ball 
{
private:
    SDL_Rect rect;
    int x;          
    int y;         
    int radius;   
    Uint32 color;
    float velocityX = 500.0f;
    float velocityY = 500.0f;

public:
    Ball(int x, int y, int radius, Uint32 color);
    ~Ball();

    void draw(SDL_Renderer* renderer) const;
    void move(float deltaTime, float dx, float dy, SDL_Rect playerRect, bool& isCatched);

    SDL_Rect getRect() const; 
    int getX() const { return x; }
    int getY() const { return y; }
    int getRadius() const { return radius; }
    float getVelocityX() const { return velocityX; }
    float getVelocityY() const { return velocityY; }

    void setPosition(int newX, int newY);
    void setVelocity(float dx, float dy); 
};
