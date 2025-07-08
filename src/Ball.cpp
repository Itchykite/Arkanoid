#include "Ball.hpp"
#include "Settings.hpp"
#include "Player.hpp"

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

void Ball::move(float deltaTime, float dx, float dy, SDL_Rect playerRect, bool& isCatched, Player*& player) 
{
    x += static_cast<int>(velocityX * deltaTime);
    y += static_cast<int>(velocityY * deltaTime);
    
    rect.x = x - radius;
    rect.y = y - radius;

    velocityX += dx * deltaTime;
    velocityY += dy * deltaTime;

    if (x - radius < 0 || x + radius > WINDOW_WIDTH) 
    {
        velocityX = -velocityX;
    }

    if (y < 0) 
    {
        velocityY = -velocityY;
    }

    if (y + radius + 2 > WINDOW_HEIGHT) 
    {
        setPosition(playerRect.x + playerRect.w / 2, playerRect.y - radius + 2);
        player->setLives(player->getLives() - 1);
        isCatched = true;
    }

    if (SDL_HasIntersection(&rect, &playerRect)) 
    {
        if (y + radius > playerRect.y && y < playerRect.y + playerRect.h) 
        {
            float paddleCenterX = playerRect.x + playerRect.w / 2.0f;
            float relativeIntersectX = (x - paddleCenterX);
            float normalizedRelativeX = relativeIntersectX / (playerRect.w / 2.0f);

            float maxBounceAngle = M_PI / 3.0f;

            float bounceAngle = normalizedRelativeX * maxBounceAngle;

            float speed = std::sqrt(velocityX * velocityX + velocityY * velocityY);

            velocityX = speed * std::sin(bounceAngle);
            velocityY = -speed * std::cos(bounceAngle);
        }
    }
}

void Ball::setPosition(int newX, int newY) 
{
    x = newX;
    y = newY;
    rect.x = x - radius;
    rect.y = y - radius;
}

void Ball::setVelocity(float dx = 500,float dy = 500) 
{
    velocityX = dx;
    velocityY = dy;
}

SDL_Rect Ball::getRect() const 
{
    return SDL_Rect{static_cast<int>(x - radius), static_cast<int>(y - radius), radius * 2, radius * 2};
}
