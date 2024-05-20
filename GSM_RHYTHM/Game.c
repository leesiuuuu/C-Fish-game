#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Example.h"

SDL_Renderer* Renderer = NULL;
SDL_Window* window = NULL;
TTF_Font* font = NULL;
TTF_Font* countFont = NULL;
SDL_Texture* fish = NULL;
SDL_Texture* startimg = NULL;
SDL_Texture* background = NULL;
SDL_Texture* fishgame = NULL;
SDL_Texture* start = NULL;
SDL_Texture* quit1 = NULL;
SDL_Texture* fishselete = NULL;
SDL_Texture* gameback = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 초기화 실패! SDL Error : %s\n", SDL_GetError());
        return false;
    }
    
    if (TTF_Init() == -1) {
        printf("SDL_ttf 초기화 실패! SDL_ttf Error : %s\n", TTF_GetError());
        return false;
    }

    window = SDL_CreateWindow("Bird Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL 창을 불러오지 못했습니다! SDL Error : %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == NULL) {
        printf("SDL 랜더러를 불러오지 못했습니다! SDL_image Error : %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Renderer);

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
        printf("SDL_image를 초기화할 수 없습니다! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer 초기화에 실패했습니다! SDL_Mixer Error : %s\n", Mix_GetError());
        return false;
    }

    font = TTF_OpenFont("Font/DungGeunMo.otf", 60);
    if (font == NULL) {
        printf("폰트를 열 수 없습니다!\n");
        return false;
    }


    return true;
}

bool loadMedia() {
    fish = IMG_LoadTexture(Renderer, "Image/Game/fish2.png");
    startimg = IMG_LoadTexture(Renderer, "Image/Game/startimg.png");
    fishgame = IMG_LoadTexture(Renderer, "Image/Game/Fish game.png");
    background = IMG_LoadTexture(Renderer, "Image/Game/background.png");
    start = IMG_LoadTexture(Renderer, "Image/Game/start.png");
    quit1 = IMG_LoadTexture(Renderer, "Image/game/quit.png");
    fishselete = IMG_LoadTexture(Renderer, "Image/game/fishopen.png");

    Texture_Check(fish);
    Texture_Check(fishselete);
    Texture_Check(startimg);    
    Texture_Check(fishgame);
    Texture_Check(background);
    Texture_Check(start);
    Texture_Check(quit1);
    return true;
}

bool gameMedia() {
    fish = IMG_LoadTexture(Renderer, "Image/Game/fish2.png");
    gameback = IMG_LoadTexture(Renderer, "Image/Game/gameback.png");

    Texture_Check(fish);
    Texture_Check(gameback);
}


void close() {
    //SDL_DestroyTexture(Texture);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    //Mix_FreeMusic(music);
    Mix_CloseAudio();
    window = NULL;
    Renderer = NULL;
    font = NULL;
    countFont = NULL;
     fish = NULL;
    startimg = NULL;
    background = NULL;
    fishgame = NULL;
    start = NULL;
    quit1 = NULL;
    fishselete = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!init()) {
        printf("SDL 초기화에 실패하였습니다!\n");
        return false;
    }
    if (!loadMedia()) {
        printf("이미지를 불러오는데 실패했습니다!\n");
        return false;
    }
    /*
    SDL_Color black = { 0, 0, 0, 0 };
    SDL_Surface* surface = TTF_RenderText_Blended(font, "Fish Game", black);
    SDL_Surface* countsurface = TTF_RenderText_Blended(font, "SCORE : ", black);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, surface);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(Renderer, countsurface);
    Texture_Check(texture);
    Texture_Check(texture2);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(countsurface);
    SDL_Rect r = { 185, 180, surface->w, surface->h };
    SDL_Rect r2 = { 0, 0, countsurface->w, countsurface->h };
    //SDL_RenderCopy(Renderer, texture2, NULL, &r2);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);
    TTF_CloseFont(font);
    */

    bool isDestroyed = false;
    bool gameStart = false;
    bool selete = false;
    bool start1 = false;

    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym)
                {
                case SDLK_DOWN:
                    selete = true;
                    break;
                case SDLK_UP:
                    selete = false;
                    break;

                case SDLK_SPACE:
                    start1 = true;
                    break;
                }
            }

        }
        if (isDestroyed == false) {
            SDL_RenderCopy(Renderer, startimg, NULL, NULL);
            SDL_RenderPresent(Renderer);
            SDL_Delay(2000);
            for (int i = 255; i >= 0; i -= 2)
            {
                SDL_RenderClear(Renderer);
                SDL_SetTextureAlphaMod(startimg, i);
                SDL_RenderCopy(Renderer, startimg, NULL, NULL);
                SDL_RenderPresent(Renderer);
            }
            isDestroyed = true;
        }
        SDL_RenderClear(Renderer);
        if (isDestroyed == true && gameStart == false) {
            loadMedia();
            SDL_RenderCopy(Renderer, background, NULL, NULL);
            SDL_RenderCopy(Renderer, fishgame, NULL, NULL);
            SDL_RenderCopy(Renderer, start, NULL, NULL);
            SDL_RenderCopy(Renderer, quit1, NULL, NULL);
            if (selete == false) {
                stretchTexture(Renderer, 170, 215, 80, 80, fish);
                if (start1 == true && selete == false) {
                    printf("게임 시작!\n");
                    stretchTexture(Renderer, 170, 215, 80, 80, fishselete);
                    SDL_Delay(1000);
                    start1 = false;
                    gameStart = true;
                }
            }
            else {
                stretchTexture(Renderer, 170, 275, 80, 80, fish);
                if (start1 == true && selete == true) {
                    printf("게임 종료!");
                    close();
                }
            }
            SDL_RenderPresent(Renderer);
        }
        if (gameStart == true) {
            
            selete = false;
            
            
        }
    }
    close();
    return 0;
}