#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Example.h"
#include <stdlib.h>
#include <time.h>

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
SDL_Texture* barrier = NULL;
Mix_Music* music = NULL;
Mix_Music* gameMusic = NULL;
Mix_Chunk* StartSound = NULL;
Mix_Chunk* JumpSound = NULL;
Mix_Chunk* seleteSound = NULL;
SDL_Texture* Death = NULL;
Mix_Chunk* DeathSound = NULL;


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
    quit1 = IMG_LoadTexture(Renderer, "Image/Game/quit.png");
    fishselete = IMG_LoadTexture(Renderer, "Image/Game/fishopen.png");
    gameback = IMG_LoadTexture(Renderer, "Image/Game/gameback.png");
    ready = IMG_LoadTexture(Renderer, "Image/Game/Ready.png");
    go = IMG_LoadTexture(Renderer, "Image/Game/Go.png");
    music = Mix_LoadMUS("Songs/mainSong1.wav");
    barrier = IMG_LoadTexture(Renderer, "Image/Game/barrier.png");
    gameMusic = Mix_LoadMUS("Songs/gameSong.wav");
    Death = IMG_LoadTexture(Renderer, "Image/Game/gameover.png");
    

    if (fish == NULL || startimg == NULL || fishgame == NULL || background == NULL ||
        start == NULL || quit1 == NULL || fishselete == NULL || gameback == NULL ||
        ready == NULL || go == NULL || barrier == NULL || Death == NULL) {
        printf("이미지를 로드하는 데 실패했습니다!\n");
        return false;
    }
    if (music == NULL) {
        printf("음악을 로드하는 데 실패했습니다!\n");
        return false;
    }
    if (gameMusic == NULL) {
        printf("음악을 로드하는 데 실패했습니다!\n");
        return false;
    }

    return true;
}

bool AudioSound() {
    StartSound = Mix_LoadWAV("Sound/start.wav");
    if (!StartSound) {
        printf("효과음을 불러오지 못했습니다!\n");
        return false;
    }
    JumpSound = Mix_LoadWAV("Sound/jump.wav");
    if (!JumpSound) {
        printf("효과음을 불러오지 못했습니다!\n");
        return false;
    }
    seleteSound = Mix_LoadWAV("Sound/selete1.wav");
    if (!seleteSound) {
        printf("효과음을 불러오지 못했습니다!\n");
        return false;
    }
    DeathSound = Mix_LoadWAV("Sound/death.wav");
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
    SDL_DestroyTexture(barrier);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int y = 100;
int x = 550;
//장애물 y값 범위
int a = -300;
int b = 0;


bool gameover = false;

bool Jump = false;

bool startBarrier = false;

void GravitySetting() { //물고기의 움직임 조절 함수
    y += 2; // 물고기를 떨어뜨리는 코드
    if (y > 480) { //바닥으로 떨어졌을 때 게임오버 화면 뜨게 하는 코드
        y = 100;
        gameover = true;
    }
    if (Jump == true) {
        if (y < 0) //물고기가 화면을 넘어가는 걸 방지하는 코드
            y = 0;
        for (int i = 0; i < 10; i++)
        {
            y -= 6;
            Jump = false;
        }
        
    }
    // 장애물 움직임 코드
    x -= 4;
    if (x < -300) {
        x = 550;
        startBarrier = false;
    }
    // 물고기 오브젝트를 넘어갈 시 신호를 보냄
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
    bool startAudio = false;
    bool MusicStart = false;
    bool gameMusicstart = false;
    bool gameMusicend = false;
    bool isDestroyed = false;
    bool gameStart = false;
    bool selete = false;
    bool start1 = false;
    bool Ready = true;
    bool readyDelete = false;
    bool DeathMenu = false;
    int y1 = 0;

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) { //키 이벤트를 받는 코드
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                AudioSound();
                switch (event.key.keysym.sym) {
                case SDLK_DOWN:
                    if(gameStart == false)
                        Mix_PlayChannel(-1, seleteSound, 0);
                    selete = true;
                    break;
                case SDLK_UP:
                    if(gameStart == false)
                        Mix_PlayChannel(-1, seleteSound, 0);
                    selete = false;
                    break;
                case SDLK_SPACE:
                    start1 = true;
                    break;
                case SDLK_z:
                    if(gameStart == true)
                        Mix_PlayChannel(-1, JumpSound, 0);
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
        if (isDestroyed == true && gameStart == false && DeathMenu == false) {
            if (MusicStart == false) {
                Mix_PlayMusic(music, -1);
                MusicStart = true;
            }
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
                    return 0;
                }
            }

            SDL_RenderPresent(Renderer);
        }
        if (gameStart == true) {
            AudioSound();
            if (startAudio == false) {
                Mix_FreeMusic(music);
                Mix_PlayChannel(-1, StartSound, 0);
                startAudio = true;
            }
            SDL_RenderCopy(Renderer, gameback, NULL, NULL);
            srand((unsigned)time(NULL));
            if (Ready == true) {
                stretchTexture(Renderer, 150, y, 100, 100, fish);
                for (int i = 255; i >= 0; i-=5)
                {
                    SDL_RenderClear(Renderer);
                    SDL_RenderCopy(Renderer, gameback, NULL, NULL);
                    stretchTexture(Renderer, 150, y, 100, 100, fish);
                    SDL_SetTextureAlphaMod(ready, i);
                    SDL_RenderCopy(Renderer, ready, NULL, NULL);
                    SDL_RenderPresent(Renderer);
                } //Ready 글자 점점 사리지게 하는 for 문
                SDL_RenderPresent(Renderer);
                SDL_RenderCopy(Renderer, go, NULL, NULL);
                SDL_RenderPresent(Renderer);
                SDL_Delay(1000);
                SDL_DestroyTexture(go);
                SDL_RenderPresent(Renderer);
                Ready = false;
            }
            else {
                if (startBarrier == true) {
                    y1 = rand() % (b - a + 1) + a;
                    startBarrier = false;
                }
                if (gameMusicstart == false) {
                    Mix_PlayMusic(gameMusic, -1);
                    gameMusicstart = true;
                }
                    
                GravitySetting();
                stretchTexture(Renderer, 150, y, 100, 100, fish);
                stretchTexture(Renderer, x, y1, 400, 800, barrier);
                SDL_RenderPresent(Renderer);
            }
        }
        if (gameover == true) {
            if (gameMusicend == false) {
                Mix_FreeMusic(gameMusic);            
                Mix_PlayChannel(-1, DeathSound, 0);
                gameMusicend = true;
            }
            gameStart = false;
            DeathMenu = true;
            SDL_RenderClear(Renderer);

            SDL_RenderCopy(Renderer, background, NULL, NULL);
            SDL_RenderCopy(Renderer, fishselete, NULL, NULL);
            SDL_RenderCopy(Renderer, Death, NULL, NULL);
            SDL_RenderPresent(Renderer);
            SDL_Delay(2000);
            DeathMenu = false;
            MusicStart = false;
            gameover = false;
            printf("게임오버됨!\n");
        }
    }

    close();
    return 0;
}
