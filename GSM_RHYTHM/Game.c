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
SDL_Texture* ready = NULL;
SDL_Texture* go = NULL;

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
    gameback = IMG_LoadTexture(Renderer, "Image/Game/gameback.png");
    ready = IMG_LoadTexture(Renderer, "Image/Game/Ready.png");
    go = IMG_LoadTexture(Renderer, "Image/Game/Go.png");

    if (fish == NULL || startimg == NULL || fishgame == NULL || background == NULL ||
        start == NULL || quit1 == NULL || fishselete == NULL || gameback == NULL ||
        ready == NULL || go == NULL) {
        printf("이미지를 로드하는 데 실패했습니다!\n");
        return false;
    }

    return true;
}

void close() {
    //SDL_DestroyTexture(Texture);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    //Mix_FreeMusic(music);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_DestroyTexture(fish);
    SDL_DestroyTexture(startimg);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(fishgame);
    SDL_DestroyTexture(start);
    SDL_DestroyTexture(quit1);
    SDL_DestroyTexture(fishselete);
    SDL_DestroyTexture(gameback);
    SDL_DestroyTexture(ready);
    SDL_DestroyTexture(go);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int y = 100;

bool gameover = false;

bool Jump = false;

void GravitySetting() {
    y += 3;
    if (y > 480) {
        y = 100;
        gameover = true;
    }
    if (Jump == true) {
        for (int i = 0; i < 10; i++)
        {
            y -= 8;
            Jump = false;
        }
        
    }
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

    bool isDestroyed = false;
    bool gameStart = false;
    bool selete = false;
    bool start1 = false;
    bool Ready = true;

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_DOWN:
                    selete = true;
                    break;
                case SDLK_UP:
                    selete = false;
                    break;
                case SDLK_SPACE:
                    start1 = true;
                    break;
                case SDLK_z:
                    Jump = true;
                    break;
                }
            }
        }

        if (isDestroyed == false) {
            SDL_RenderCopy(Renderer, startimg, NULL, NULL);
            SDL_RenderPresent(Renderer);
            SDL_Delay(2000);
            for (int i = 255; i >= 0; i -= 2) {
                SDL_RenderClear(Renderer);
                SDL_SetTextureAlphaMod(startimg, i);
                SDL_RenderCopy(Renderer, startimg, NULL, NULL);
                SDL_RenderPresent(Renderer);
            }
            isDestroyed = true;
        }

        SDL_RenderClear(Renderer);

        if (isDestroyed == true && gameStart == false) {
            SDL_RenderCopy(Renderer, background, NULL, NULL);
            SDL_RenderCopy(Renderer, fishgame, NULL, NULL);
            SDL_RenderCopy(Renderer, start, NULL, NULL);
            SDL_RenderCopy(Renderer, quit1, NULL, NULL);

            if (selete == false) {
                stretchTexture(Renderer, 170, 215, 80, 80, fish);
                if (start1 == true && selete == false) {
                    printf("게임 시작!\n");
                    stretchTexture(Renderer, 170, 215, 80, 80, fishselete);
                    start1 = false;
                    SDL_Delay(300);
                    SDL_RenderClear(Renderer);
                    gameStart = true;
                    selete = true;
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
            SDL_RenderCopy(Renderer, gameback, NULL, NULL);

            if (Ready == true) {
                stretchTexture(Renderer, 150, y, 100, 100, fish);
                SDL_RenderCopy(Renderer, ready, NULL, NULL);
                SDL_RenderPresent(Renderer);
                SDL_Delay(1000);
                SDL_DestroyTexture(ready);
                SDL_RenderCopy(Renderer, go, NULL, NULL);
                SDL_RenderPresent(Renderer);
                SDL_Delay(1000);
                SDL_DestroyTexture(go);
                SDL_RenderPresent(Renderer);
                Ready = false;
            }
            else {
                GravitySetting();
                stretchTexture(Renderer, 150, y, 100, 100, fish);
                SDL_RenderPresent(Renderer);
            }
        }
    }

    close();
    return 0;
}
