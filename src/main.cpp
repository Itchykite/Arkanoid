#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "Settings.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "Level.hpp"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
bool isRunning = true;
bool isCatched = false;
TTF_Font* font = nullptr;

Player* player = nullptr;
Ball* ball = nullptr;
Level* level = nullptr;

bool initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return false;
    }

    SDL_Log("Creating window...");
    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if(!window)
    {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }
    SDL_Log("SUCCESS!");

    SDL_Log("Creating renderer...");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer)
    {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }
    SDL_Log("SUCCESS!");

    SDL_Log("Creating player...");
    player = new Player(1, 3, SDL_Rect{WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT - 20, 300, 20});
    if(!player)
    {
        printf("Failed to create player object.\n");
        return false;
    }
    SDL_Log("SUCCESS!");

    SDL_Log("Creating ball");
    ball = new Ball(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 28, 10, 0xFFFFFFFF);
    if(!ball)
    {
        printf("Failed to create ball object.\n");
        return false;
    }
    SDL_Log("SUCCESS!");

    SDL_Log("Creating level...");
    level = new Level();
    if(!level)
    {
        printf("Failed to create level object.\n");
        return false;
    }
    SDL_Log("SUCCESS!\n");

    SDL_Log("Initializing TTF...");
    if(TTF_Init() == -1)
    {
        SDL_Log("TTF could not initialize! TTF_Error: %s", TTF_GetError());
        return false;
    }
    SDL_Log("SUCCESS!");

    SDL_Log("Loading font...");
    font = TTF_OpenFont("../fonts/roboto-bold.ttf", 24); 
    if(!font)
    {
        SDL_Log("Failed to load font! TTF_Error: %s", TTF_GetError());
        return false;
    }
    SDL_Log("SUCCESS!");

    SDL_Log("Everything initialized");

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
    else 
    {
        isCatched = false;
    }
}

void handleMovement(float deltaTime) 
{
    const Uint8* keystates = SDL_GetKeyboardState(nullptr);

    if(keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A])
    {
        player->move(deltaTime, -player->getMoveLeft(), 0);
    }
    else if(keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D])
    {
        player->move(deltaTime, player->getMoveRight(), 0);
    }

    if(keystates[SDL_SCANCODE_SPACE])
    {
        if(isCatched)
        {
            ball->setPosition(ball->getX(), ball->getY() - 5);
            ball->setVelocity(0, -500); 
        }
    }

    if(keystates[SDL_SCANCODE_R])
    {
        level->reset(ball);
        player->setLives(3);
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

        handleMovement(deltaTime);

        collisionDetection();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        level->draw(renderer);
        level->removeBrick(ball->getRect(), *&ball, ball->getRect(), *&player);

        player->render(renderer);
        ball->draw(renderer);
        ball->move(deltaTime, 0, 0, player->getRect(), isCatched);

        renderText(renderer, font, "Level: " + std::to_string(Level::getLevelNumber()), 10, 10);
        renderText(renderer, font, "Broken bricks: " + std::to_string(player->getBlocksBreaked()), 10, 40);
        
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

    if(level)
    {
        delete level;
        level = nullptr;
    }

    if(font)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }

    TTF_Quit();
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
