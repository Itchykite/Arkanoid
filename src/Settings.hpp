#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y);
