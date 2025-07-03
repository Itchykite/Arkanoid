#include "Ball.hpp"

Ball::Ball(int x, int y, int radius, Uint32 color)
    : x(x), y(y), radius(radius), color(color), rect{ x - radius, y - radius, radius * 2, radius * 2 } 
{
    
}

Ball::~Ball() 
{

}

void Ball::draw(SDL_Renderer* renderer) const 
{
    filledCircleColor(renderer, x, y, radius, color);
}

void Ball::move(float deltaTime, float dx, float dy) 
{
    x += static_cast<int>(velocityX * deltaTime);
    y += static_cast<int>(velocityY * deltaTime);
    
    rect.x = x - radius;
    rect.y = y - radius;

    velocityX += dx * deltaTime;
    velocityY += dy * deltaTime;
}

void Ball::setPosition(int newX, int newY) 
{
    x = newX;
    y = newY;
    rect.x = x - radius;
    rect.y = y - radius;
}

void Ball::setVelocity(float dx, float dy) 
{
    velocityX = dx;
    velocityY = dy;
}
