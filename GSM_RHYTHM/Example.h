#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

SDL_Renderer* Renderer2 = NULL;


SDL_Texture* Texture_Check(SDL_Texture* Tex) {
    if (Tex == NULL) {
        printf("UI이미지를 불러올 수 없습니다! SDL_image Error : %s\n", IMG_GetError());
    }
    return false;
}

bool Audio_Check(Mix_Music* Aud) {
    if (Aud == NULL) {
        printf("오디오를 불러올 수 없습니다! SDL_Mixer Error : %s\n", Mix_GetError());
    }
    return false;
}


void stretchTexture(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Texture* texture) {
    SDL_Rect src, dst;

    src.x = src.y = 0;
    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(renderer, texture, &src, &dst);
}

SDL_Texture* changeTexture(SDL_Renderer* renderer, const char* file) {
    SDL_Texture* changedTex = IMG_LoadTexture(renderer, file);
    if (changedTex == NULL) {
        printf("텍스처를 변경할 수 없습니다! SDL_image Error: %s\n", IMG_GetError());
    }
    return changedTex;
}


