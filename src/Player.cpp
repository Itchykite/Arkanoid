#include "Player.hpp"
#include "Settings.hpp"

Player::Player(int s, int l, int li, const SDL_Rect &r) : score(s), level(l), lives(li), rect(r) 
{
    
};

Player::~Player() 
{

}

void Player::render(SDL_Renderer* renderer) 
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &rect);
}

void Player::move(float deltaTime, float dx, float dy) 
{
    rect.x += dx * deltaTime;
    rect.y += dy * deltaTime;

    if (rect.x < 0) { rect.x = 0; }
    if (rect.y < 0) { rect.y = 0; }
    if (rect.x + rect.w > WINDOW_WIDTH) { rect.x = WINDOW_WIDTH - rect.w; }
    if (rect.y + rect.h > WINDOW_HEIGHT) { rect.y = WINDOW_HEIGHT - rect.h; } 
}

int Player::getScore() const 
{
    return score;
}

void Player::setScore(int newScore) 
{
    score = newScore;
}

int Player::getLevel() const 
{
    return level;
}

void Player::setLevel(int newLevel) 
{
    level = newLevel;
}

int Player::getLives() const 
{
    return lives;
}

void Player::setLives(int newLives) 
{
    lives = newLives;
}

SDL_Rect Player::getRect() const 
{
    return rect;
}
