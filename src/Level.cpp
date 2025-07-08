#include "Level.hpp"
#include "Ball.hpp"
#include "Settings.hpp"
#include "Player.hpp"

int Level::levelNumber = 1;

Uint32 generateColor()
{
    Uint32 r = std::rand() % 256;
    Uint32 g = std::rand() % 256;
    Uint32 b = std::rand() % 256;
    return (r << 16) | (g << 8) | b;
}

Level::Level() 
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

    Uint32 color1 = generateColor();
    Uint32 color2 = generateColor();

    for (int row = 0; row < rows; ++row) 
    {
        for (int col = 0; col < cols; ++col) 
        {
            int x = marginX + col * (brickWidth + spacingX);
            int y = marginY + row * (brickHeight + spacingY);
            Uint32 color = (row % 2 == 0) ? color1 : color2; 
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
    levelNumber++;
    int rows = 5 + levelNumber;
    int cols = 10; 
    int spacingX = 8;
    int spacingY = 5;
    int marginX = 50; 
    int marginY = 50; 

    int totalSpacingX = (cols - 1) * spacingX;
    int brickWidth = (WINDOW_WIDTH - 2 * marginX - totalSpacingX) / cols;
    int brickHeight = 20; 

    Uint32 color1 = generateColor();
    Uint32 color2 = generateColor();

    for (int row = 0; row < rows; ++row) 
    {
        for (int col = 0; col < cols; ++col) 
        {
            int x = marginX + col * (brickWidth + spacingX);
            int y = marginY + row * (brickHeight + spacingY);
            Uint32 color = (row % 2 == 0) ? color1 : color2; 
            bricks.emplace_back(x, y, brickWidth, brickHeight, color);
        }
    }
}

bool Level::isComplete() const 
{
    return bricks.empty();
}

void Level::removeBrick(SDL_Rect ballRect, Ball*& ball, SDL_Rect playerRect, Player*& player) 
{
    for (auto it = bricks.begin(); it != bricks.end(); ) 
    {
        SDL_Rect brickRect = it->getRect();
        if (SDL_HasIntersection(&ballRect, &brickRect)) 
        {
            it = bricks.erase(it);
         
            Player::setBlocksBreaked(Player::getBlocksBreaked() + 1);

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
                reset(ball);
            }

            return; 
        }
        
        if(Player::getBlocksBreaked() == 5) 
        {
            Player::setBlocksBreaked(0);
            player->setMoveLeft(player->getMoveLeft() * 1.05f);
            player->setMoveRight(player->getMoveRight() * 1.05f);
            ball->setVelocity(ball->getVelocityX() * 1.05f, ball->getVelocityY() * 1.05f);
        }

        else 
        {
            ++it;
        }
    }
}
