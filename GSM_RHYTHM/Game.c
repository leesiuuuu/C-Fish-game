#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Example.h"
#include <stdlib.h>
#include <time.h>
#include "Intro.h"
#include "Setting.h"
#include "Player.h"

// ������, â
SDL_Renderer* Renderer = NULL;
SDL_Window* window = NULL;

//��Ʈ
TTF_Font* font = NULL;
TTF_Font* countFont = NULL;

//�̹���
SDL_Texture* fish = NULL;
SDL_Texture* startimg = NULL;
SDL_Texture* background = NULL;
SDL_Texture* fishgame = NULL;
SDL_Texture* start = NULL;
SDL_Texture* quit1 = NULL;
SDL_Texture* setting = NULL;
SDL_Texture* fishselete = NULL;
SDL_Texture* gameback = NULL;
SDL_Texture* ready = NULL;
SDL_Texture* go = NULL;
SDL_Texture* barrier = NULL;
SDL_Texture* Death = NULL;
SDL_Texture* CheckConsole = NULL;
SDL_Texture* SetWindow = NULL;

//�Ҹ�
Mix_Music* music = NULL;
Mix_Music* gameMusic = NULL;
Mix_Chunk* StartSound = NULL;
Mix_Chunk* JumpSound = NULL;
Mix_Chunk* seleteSound = NULL;
Mix_Chunk* DeathSound = NULL;

// ���� ����
int SoundSetting = 100;

// ��������Ʈ �ִϸ��̼�
SDL_Surface* window_surface = NULL;
SDL_Surface* player_surface = NULL;
SDL_Surface* background_surface = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL �ʱ�ȭ ����! SDL Error : %s\n", SDL_GetError());
        return false;
    }
    
    if (TTF_Init() == -1) {
        printf("SDL_ttf �ʱ�ȭ ����! SDL_ttf Error : %s\n", TTF_GetError());
        return false;
    }

    window = SDL_CreateWindow("Awesome Fish Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL â�� �ҷ����� ���߽��ϴ�! SDL Error : %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == NULL) {
        printf("SDL �������� �ҷ����� ���߽��ϴ�! SDL_image Error : %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(Renderer);

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
        printf("SDL_image�� �ʱ�ȭ�� �� �����ϴ�! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer �ʱ�ȭ�� �����߽��ϴ�! SDL_Mixer Error : %s\n", Mix_GetError());
        return false;
    }

    font = TTF_OpenFont("Font/DungGeunMo.otf", 60);
    if (font == NULL) {
        printf("��Ʈ�� �� �� �����ϴ�!\n");
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
    setting = IMG_LoadTexture(Renderer, "Image/Game/setting.png");
    fishselete = IMG_LoadTexture(Renderer, "Image/Game/fishopen.png");
    gameback = IMG_LoadTexture(Renderer, "Image/Game/gameback.png");
    ready = IMG_LoadTexture(Renderer, "Image/Game/Ready.png");
    go = IMG_LoadTexture(Renderer, "Image/Game/Go.png");
    music = Mix_LoadMUS("Songs/mainSong1.wav");
    barrier = IMG_LoadTexture(Renderer, "Image/Game/barrier.png");
    gameMusic = Mix_LoadMUS("Songs/gameSong.wav");
    Death = IMG_LoadTexture(Renderer, "Image/Game/gameover.png");
    SetWindow = IMG_LoadTexture(Renderer, "Image/Game/SettingWindow.png");
    CheckConsole = IMG_LoadTexture(Renderer, "Image/Game/CheckConsole.png");


    if (fish == NULL || startimg == NULL || fishgame == NULL || background == NULL ||
        start == NULL || quit1 == NULL || fishselete == NULL || gameback == NULL ||
        ready == NULL || go == NULL || barrier == NULL || Death == NULL || setting == NULL || SetWindow == NULL || CheckConsole == NULL) {
        printf("�̹����� �ε��ϴ� �� �����߽��ϴ�!\n");
        return false;
    }
    if (music == NULL) {
        printf("������ �ε��ϴ� �� �����߽��ϴ�!\n");
        return false;
    }
    if (gameMusic == NULL) {
        printf("������ �ε��ϴ� �� �����߽��ϴ�!\n");
        return false;
    }
    return true;
}

bool AudioSound() {
    StartSound = Mix_LoadWAV("Sound/start.wav");
    if (!StartSound) {
        printf("ȿ������ �ҷ����� ���߽��ϴ�!\n");
        return false;
    }
    JumpSound = Mix_LoadWAV("Sound/jump.wav");
    if (!JumpSound) {
        printf("ȿ������ �ҷ����� ���߽��ϴ�!\n");
        return false;
    }
    seleteSound = Mix_LoadWAV("Sound/selete1.wav");
    if (!seleteSound) {
        printf("ȿ������ �ҷ����� ���߽��ϴ�!\n");
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

bool gameover = false;

bool startBarrier = false;

int main(int argc, char* argv[]) {
    if (!init()) {
        printf("SDL �ʱ�ȭ�� �����Ͽ����ϴ�!\n");
        return false;
    }
    if (!loadMedia()) {
        printf("�̹����� �ҷ����µ� �����߽��ϴ�!\n");
        return false;
    }      

    bool startAudio = false;
    bool MusicStart = false;
    bool gameMusicstart = false;
    bool gameMusicend = false;
    bool isDestroyed = false;
    bool SettingWindow = false;
    bool gameStart = false;
    int seleteState = 0;
    bool start1 = false;
    bool Ready = true;
    bool readyDelete = false;
    bool DeathMenu = false;
    bool SoundSetComplete = false;
    bool ClearRenderer = false;
    bool SoundOn = false;
    int y1 = 0;

    SDL_Event event;
    int quit = 0;

    
    SDL_Rect rcSprite = { 0, 0, 100, 100 };
    int fish_idx = 0;
    int fish_jump_idx = 0;
    int fish_state = 0;
    bool isJumping = false;

    window_surface = SDL_GetWindowSurface(window);
    if (window_surface == NULL) {
        printf("Failed to get window surface! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    //��� �̹��� �ε�
    background_surface = SDL_LoadBMP("Image/Player/background.bmp");
    if (background_surface == NULL) {
        printf("Failed to load background image! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    // �÷��̾� �̹��� �ε�
    player_surface = SDL_LoadBMP("Image/Game/fish_Padak-Sheet.bmp");
    if (player_surface == NULL) {
        printf("Failed to load player image! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(background_surface);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    //�÷��̾� �̹��� ��� �����ϰ� �ϱ�
    SDL_SetColorKey(player_surface, SDL_TRUE, SDL_MapRGB(player_surface->format, 255, 0, 255));

    loadMedia();
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) { //Ű �̺�Ʈ�� �޴� �ڵ�
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                AudioSound();
                switch (event.key.keysym.sym) {
                case SDLK_DOWN:
                    if (gameStart == false && SettingWindow == false) {
                        Mix_Volume(-1, SoundSetting);
                        Mix_PlayChannel(-1, seleteSound, 0);
                    }
                    ++seleteState;
                    if (seleteState > 2) {
                        seleteState = 0;
                    }
                    break;
                case SDLK_UP:
                    if (gameStart == false && SettingWindow == false) {
                        Mix_Volume(-1, SoundSetting);
                        Mix_PlayChannel(-1, seleteSound, 0);
                    }
                    --seleteState;
                    if (seleteState < 0) {
                        seleteState = 2;
                    }
                    break;
                case SDLK_SPACE:
                    if (gameStart == false) {
                        if (seleteState == 0) {
                            printf("���� ����!\n");
                            gameStart = true;
                            ClearRenderer = true;
                        }
                        if (seleteState == 1) {
                            printf("����â\n");
                            SettingWindow = true;
                        }
                        if (seleteState == 2){
                            printf("���� ����!\n");
                            close();
                        }
                    }
                    break;
                case SDLK_z:
                    if (gameStart == true && SettingWindow == false) {
                        if (SoundOn == false) {
                            Mix_Volume(-1, SoundSetting);
                            Mix_PlayChannel(-1, JumpSound, 0);
                            SoundOn = true;
                        }
                        isJumping = true;
                        fish_state = 1;
                    }
                    break;
                }
                
            }
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym)
                {
                case SDLK_z:
                    if (gameStart == true && SettingWindow == false) {
                        isJumping = false;
                        fish_state = 0;
                        SoundOn = false;
                    }
                    break;
                }
            }
        }
        SDL_RenderCopy(Renderer, background, NULL, NULL);
        // ùȭ�� ����
        if (isDestroyed == false) {
            intro(Renderer, startimg);
            isDestroyed = true;
        }
        // ���� ȭ�� ����
        if (isDestroyed == true && gameStart == false && DeathMenu == false && SettingWindow == false) {
            SDL_RenderClear(Renderer);
            //���� ���� ����
            if (MusicStart == false && SoundSetComplete == false) {
                Mix_PlayMusic(music, -1);
                MusicStart = true;
            }
            if (MusicStart == true && SoundSetComplete == true) {
                Mix_PauseMusic();
                Mix_VolumeMusic(SoundSetting);
                Mix_ResumeMusic();
                SoundSetComplete = false;
            }
            SDL_RenderCopy(Renderer, background, NULL, NULL);
            SDL_RenderCopy(Renderer, fishgame, NULL, NULL);
            SDL_RenderCopy(Renderer, start, NULL, NULL);
            SDL_RenderCopy(Renderer, setting, NULL, NULL);
            SDL_RenderCopy(Renderer, quit1, NULL, NULL);
            switch (seleteState)
            {
            case 0:
                stretchTexture(Renderer, 170, 215, 80, 80, fish);
                break;
            case 1:
                stretchTexture(Renderer, 130, 275, 80, 80, fish);
                break;
            case 2:
                stretchTexture(Renderer, 180, 325, 80, 80, fish);
                break;
            }
            SDL_RenderPresent(Renderer);
        }
        // ����â ����
        if (gameStart == false && DeathMenu == false && SettingWindow == true) {
            Setting(Renderer, background, SetWindow, CheckConsole);
            SoundSettingWindow();
            printf("\n���� ���� : %d\n", SoundSetting);
            SoundSetComplete = true;
            SettingWindow = false;
        }
        // ���� �۵� ����
        // ���� ���� �� �������� ������� ���� -> Texture�� �ƴ� Surface�� ����
        if (gameStart == true && DeathMenu == false && SettingWindow == false) {
            if (ClearRenderer == true) {
            SDL_RenderClear(Renderer);
            SDL_RenderPresent(Renderer);
            ClearRenderer = false;
            }
            if (isJumping == false) {
                fish_idx++;
                rcSprite.x = 100 * fish_idx;
                rcSprite.y = 100 * fish_state;
                if (fish_idx >= 7)
                    fish_idx = 0;
            }
            if (isJumping == true) {
                rcSprite.y = 100 * fish_state;
                rcSprite.x = 100 * fish_jump_idx;
                fish_jump_idx++;
                if (fish_jump_idx >= 5)
                    fish_jump_idx = 0;
            }
            SDL_BlitSurface(background_surface, NULL, window_surface, NULL);
            SDL_BlitSurface(player_surface, &rcSprite, window_surface, NULL);
            SDL_UpdateWindowSurface(window);
            SDL_Delay(100);
        }
    }
    close();
    return 0;
}
