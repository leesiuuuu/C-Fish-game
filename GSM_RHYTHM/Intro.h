#include <SDL.h>

void intro(SDL_Renderer* renderer, SDL_Texture* texture){
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    for (int i = 255; i >= 0; i -= 2) {
        SDL_RenderClear(renderer);
        SDL_SetTextureAlphaMod(texture, i);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}