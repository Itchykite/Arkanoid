#pragma once

#include <SDL2/SDL.h>

class Player
{
private:
    int level;
    static int lives;
    float moveLeft = 300.0f;
    float moveRight = 350.0f;
    SDL_Rect rect;
    static int blocksBreaked;

public:
    Player(int l, const SDL_Rect& r);
    ~Player();

    void render(SDL_Renderer* renderer);

    void move(float deltaTime, float dx, float dy); 

    static int getBlocksBreaked() { return blocksBreaked; }
    static void setBlocksBreaked(int newBlocksBreaked) { blocksBreaked = newBlocksBreaked; }
    int getLevel() const;
    void setLevel(int newLevel);
    int getLives() const;
    void setLives(int newLives);
    SDL_Rect getRect() const;
    float getMoveLeft() const { return moveLeft; }
    float getMoveRight() const { return moveRight; }
    void setMoveLeft(float newMoveLeft) { moveLeft = newMoveLeft; }
    void setMoveRight(float newMoveRight) { moveRight = newMoveRight; }
};
