#pragma once

#include <SDL2/SDL.h>

class Player
{
private:
    int score;
    int level;
    int lives;
    SDL_Rect rect;

public:
    Player(int s, int l, int li, const SDL_Rect& r);
    ~Player();

    void render(SDL_Renderer* renderer);

    void move(float deltaTime, float dx, float dy); 

    int getScore() const;
    void setScore(int newScore);
    int getLevel() const;
    void setLevel(int newLevel);
    int getLives() const;
    void setLives(int newLives);
    SDL_Rect getRect() const;
};
