#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_video.h>

#include "Settings.hpp"
#include "Player.hpp"
#include "Ball.hpp"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool isRunning = true;
bool isCatched = false;

Player* player = nullptr;
Ball* ball = nullptr;

bool initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if(!window)
    {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
    {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    player = new Player(0, 1, 3, SDL_Rect{WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT - 20, 300, 20});
    if(!player)
    {
        printf("Failed to create player object.\n");
        return false;
    }

    ball = new Ball(WINDOW_WIDTH / 2, WINDOW_HEIGHT + 20, 10, 0xFFFFFFFF);
    if(!ball)
    {
        printf("Failed to create ball object.\n");
        return false;
    }

    return true;
}

void handleEvents(float deltaTime)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            isRunning = false;
        }

        if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
        }
    }
}

void collisionDetection()
{
    SDL_Rect playerRect = player->getRect();
    SDL_Rect ballRect = ball->getRect();

    if(SDL_HasIntersection(&playerRect, &ballRect))
    {
        isCatched = true;
    }
}

void loop()
{
    Uint64 lastTime = SDL_GetPerformanceCounter();
    float deltaTime = 0.0f;

    SDL_Event event;
    while(isRunning)
    {
        Uint64 currentTime = SDL_GetPerformanceCounter();
        float deltaTime = (currentTime - lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
        lastTime = currentTime;
        if(deltaTime > 0.05f) deltaTime = 0.016f;

        handleEvents(deltaTime);

        const Uint8* keystates = SDL_GetKeyboardState(nullptr);

        if(keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A])
        {
            player->move(deltaTime, -200, 0);
            if(isCatched)
            {
                ball->move(deltaTime, -200, 0);
            }
        }
        else if(keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D])
        {
            player->move(deltaTime, 250, 0);
            if(isCatched)
            {
                ball->move(deltaTime, 250, 0);
            }
        }

        if(keystates[SDL_SCANCODE_SPACE])
        {
            if(isCatched)
            {
                isCatched = false;
                ball->setPosition(player->getRect().x + player->getRect().w / 2, player->getRect().y - ball->getRadius());
                ball->setVelocity(0, -500); 
            }
            else
            {
                ball->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT + 20);
                ball->setVelocity(0, 0);
            }
        }

        collisionDetection();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        player->render(renderer);
        ball->draw(renderer);
    
        SDL_RenderPresent(renderer);
    }
}

void cleanupSDL()
{
    if(renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if(window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    
    if(player)
    {
        delete player;
        player = nullptr;
    }

    if(ball)
    {
        delete ball;
        ball = nullptr;
    }

    SDL_Quit();
}

int main()
{
    if(!initSDL())
    {
        return -1;
    }

    loop();

    cleanupSDL(); 

    return 0;
}
