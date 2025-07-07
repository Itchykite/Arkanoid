#include "Settings.hpp"

int WINDOW_WIDTH = 1920;
int WINDOW_HEIGHT = 1080;

void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255, 255});
    if (surface == nullptr) 
    {
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
    {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface); 
}
