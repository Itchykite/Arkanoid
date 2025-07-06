#include "Level.hpp"
#include "Ball.hpp"
#include "Settings.hpp"

Level::Level(int levelNumber) 
{
    int rows = 5 + levelNumber;
    int cols = 10; 
    int spacingX = 8;
    int spacingY = 5;
    int marginX = 50; 
    int marginY = 50; 

    int totalSpacingX = (cols - 1) * spacingX;
    int brickWidth = (WINDOW_WIDTH - 2 * marginX - totalSpacingX) / cols;
    int brickHeight = 20; 

    for (int row = 0; row < rows; ++row) 
    {
        for (int col = 0; col < cols; ++col) 
        {
            int x = marginX + col * (brickWidth + spacingX);
            int y = marginY + row * (brickHeight + spacingY);
            Uint32 color = (row % 2 == 0) ? 0xFF0000FF : 0x00FF00FF; 
            bricks.emplace_back(x, y, brickWidth, brickHeight, color);
        }
    }
}

Level::~Level() 
{
    bricks.clear();
}

void Level::draw(SDL_Renderer* renderer) const 
{
    for (const auto& brick : bricks) 
    {
        brick.draw(renderer);
    }
}

void Level::reset(Ball*& ball) 
{
    if (ball) 
    {
        ball->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 28);
        ball->setVelocity(500.0f, 500.0f);
    }

    bricks.clear();
    int levelNumber = 1; 
    int rows = 5 + levelNumber;
    int cols = 10; 
    int spacingX = 8;
    int spacingY = 5;
    int marginX = 50; 
    int marginY = 50; 

    int totalSpacingX = (cols - 1) * spacingX;
    int brickWidth = (WINDOW_WIDTH - 2 * marginX - totalSpacingX) / cols;
    int brickHeight = 20; 

    for (int row = 0; row < rows; ++row) 
    {
        for (int col = 0; col < cols; ++col) 
        {
            int x = marginX + col * (brickWidth + spacingX);
            int y = marginY + row * (brickHeight + spacingY);
            Uint32 color = (row % 2 == 0) ? 0xFF0000FF : 0x00FF00FF; 
            bricks.emplace_back(x, y, brickWidth, brickHeight, color);
        }
    }
}

bool Level::isComplete() const 
{
    return bricks.empty();
}

void Level::removeBrick(SDL_Rect ballRect, Ball*& ball, SDL_Rect playerRect) 
{
    for (auto it = bricks.begin(); it != bricks.end(); ) 
    {
        SDL_Rect brickRect = it->getRect();
        if (SDL_HasIntersection(&ballRect, &brickRect)) 
        {
            it = bricks.erase(it);
            
            if (ball) 
            {
                int ballX = ball->getX();
                int ballY = ball->getY();
                int ballRadius = ball->getRadius();

                if (ballX < brickRect.x || ballX > brickRect.x + brickRect.w) 
                {
                    ball->setVelocity(-ball->getVelocityX(), ball->getVelocityY());
                } 
                else 
                {
                    ball->setVelocity(ball->getVelocityX(), -ball->getVelocityY());
                }
            }

            if (bricks.empty()) 
            {
                reset();
            }

            return; 
        } 
        else 
        {
            ++it;
        }
    }
}
