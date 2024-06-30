#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Example.h"
#include "Intro.h"
#include "Setting.h"
#include <stdlib.h>
#include <time.h>
#include "Transition.h"

// ������, â
SDL_Renderer* Renderer = NULL;
SDL_Window* window = NULL;

//��Ʈ
TTF_Font* font = NULL;
TTF_Font* countFont = NULL;
TTF_Font* PointFont = NULL;
TTF_Font* YourRateis = NULL; //������ ��ũ�� �����ִ� ��Ʈ
TTF_Font* YRIN = NULL; //���� ��ũ��... �� ����Ҷ� ���� ��Ʈ
TTF_Font* Record = NULL; //�ְ� ���� ��� ��Ʈ

TTF_Font* CoinCountFont = NULL; //������ ���� ����ϴ� ��Ʈ

//�̹���
SDL_Texture* fish = NULL;
SDL_Texture* startimg = NULL;
SDL_Texture* background = NULL;
SDL_Texture* fishgame = NULL;
SDL_Texture* UI = NULL;
SDL_Texture* fishselete = NULL;
SDL_Texture* CheckConsole = NULL;
SDL_Texture* SetWindow = NULL;
SDL_Texture* TutorialWindow = NULL;

//����
SDL_Texture* Coin = NULL;
SDL_Surface* InGameCoin = NULL;

//���� ��, �ְ� ���� ���� txt����
FILE* fp;

//�Ҹ�
Mix_Music* music = NULL;
Mix_Music* gameMusic = NULL;
Mix_Chunk* StartSound = NULL;
Mix_Chunk* JumpSound = NULL;
Mix_Chunk* seleteSound = NULL;
Mix_Chunk* DeathSound = NULL;
Mix_Chunk* ClearSound = NULL;
Mix_Chunk* CoinSound = NULL;

// ���� ����
int SoundSetting = 100;

// Ʃ�丮�� ����
bool Tutorial = false;
bool isTutorialoff = false;

// ��������Ʈ �ִϸ��̼�
SDL_Surface* window_surface = NULL;
SDL_Surface* player_surface = NULL;
SDL_Surface* background_surface = NULL;

//���ع�
SDL_Surface* Thorn = NULL;

// ��Ʈ ���
SDL_Surface* font_surface = NULL;
SDL_Color color = { 255, 255, 255, SDL_ALPHA_OPAQUE }; //�Ͼ��
SDL_Color black = { 0, 0, 0, SDL_ALPHA_OPAQUE };
SDL_Surface* Point_surface = NULL;
SDL_Surface* CoinFont_Surface = NULL;

//���� �̹�����
SDL_Texture* Skin1 = NULL; //��Ų1
SDL_Texture* Skin2 = NULL; //��Ų2
SDL_Texture* Skin3 = NULL; //��Ų3
SDL_Texture* Skin4 = NULL; //��Ų4

SDL_Texture* Slot1 = NULL;
SDL_Texture* Slot2 = NULL;
SDL_Texture* Slot3 = NULL;
SDL_Texture* Slot4 = NULL;

SDL_Texture* DefaultButton = NULL;
SDL_Texture* Slot = NULL;

// ���� ���� �����̽�
SDL_Surface* GameOver = NULL;

//������
SDL_Surface* Icon = NULL;

//�ִϸ��̼� ���
SDL_Surface* BgSprite = NULL;

//���� ���� ���
SDL_Surface* Rate = NULL; //������ ��ũ�� �˷��ִ� �����̽�
SDL_Surface* YRI = NULL; //���� ��ũ��... �� ����ϴ� �����̽�
SDL_Color Red = { 255, 0, 0, SDL_ALPHA_OPAQUE };
SDL_Color Blue = { 0, 54, 255, SDL_ALPHA_OPAQUE };
SDL_Color Pink = { 47, 190, 255, SDL_ALPHA_OPAQUE };

int CoinNum = 0;
int NewRecord = 0;

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

    font = TTF_OpenFont("Font/DungGeunMo.otf", 40);
    if (font == NULL) {
        printf("��Ʈ�� �� �� �����ϴ�!\n");
        return false;
    }

    countFont = TTF_OpenFont("Font/DungGeunMo.otf", 30);
    if (countFont == NULL) {
        printf("��Ʈ�� �� �� �����ϴ�!\n");
        return false;
    }

    PointFont = TTF_OpenFont("Font/DungGeunMo.otf", 40);
    if (PointFont == NULL) {
        printf("��Ʈ�� �� �� �����ϴ�!\n");
        return false;
    }

    YourRateis = TTF_OpenFont("Font/DungGeunMo.otf", 130);
    if (YourRateis == NULL) {
        printf("��Ʈ�� �� �� �����ϴ�!\n");
        return false;
    }

    YRIN = TTF_OpenFont("Font/DungGeunMo.otf", 35);
    if (YRIN == NULL) {
        printf("��Ʈ�� �� �� �����ϴ�!\n");
        return false;
    }

    CoinCountFont = TTF_OpenFont("Font/DungGeunMo.otf", 30);
    if (CoinCountFont == NULL) {
        printf("��Ʈ�� �� �� �����ϴ�!\n");
        return false;
    }

    Record = TTF_OpenFont("Font/DungGeunMo.otf", 30);
    if (Record == NULL) {
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
    UI = IMG_LoadTexture(Renderer, "Image/Game/UI.png");
    fishselete = IMG_LoadTexture(Renderer, "Image/Game/fishopen.png");
    music = Mix_LoadMUS("Songs/mainSong1.wav");
    gameMusic = Mix_LoadMUS("Songs/gameSong.wav");
    SetWindow = IMG_LoadTexture(Renderer, "Image/Game/SettingWindow.png");
    CheckConsole = IMG_LoadTexture(Renderer, "Image/Game/CheckConsole.png");
    TutorialWindow = IMG_LoadTexture(Renderer, "Image/Game/tutorial.png");
    Icon = IMG_Load("Image/Game/Fish_icon.bmp");
    Coin = IMG_LoadTexture(Renderer, "Image/Game/Coin.png");
    Skin1 = IMG_LoadTexture(Renderer, "Image/Game/FishDefault.png");
    Skin2 = IMG_LoadTexture(Renderer, "Image/Game/GoldFish.png");
    Skin3 = IMG_LoadTexture(Renderer, "Image/Game/fish_female.png");
    Skin4 = IMG_LoadTexture(Renderer, "Image/Game/While.png");
    Slot4 = IMG_LoadTexture(Renderer, "Image/Game/DefaultEquiped.png");
    Slot3 = IMG_LoadTexture(Renderer, "Image/Game/WhileFish.png");
    Slot2 = IMG_LoadTexture(Renderer, "Image/Game/FemaleFish.png");
    Slot1 = IMG_LoadTexture(Renderer, "Image/Game/GoldFishBuy.png");

    if (fish == NULL || startimg == NULL || fishgame == NULL || background == NULL ||
        fishselete == NULL || SetWindow == NULL || CheckConsole == NULL
        || TutorialWindow == NULL || Icon == NULL || Coin == NULL || UI == NULL) {
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
    if (!DeathSound) {
        printf("ȿ���� �ҷ����� ����!\n");
        return false;
    }
    ClearSound = Mix_LoadWAV("Sound/Clear.wav");
    if (!ClearSound) {
        printf("ȿ���� �ҷ����� ����!\n");
        return false;
    }
    CoinSound = Mix_LoadWAV("Sound/Coin.wav");
    if (!CoinSound) {
        printf("ȿ���� �ҷ����� ����!\n");
        return false;
    }
    return true;
}

void close() {
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(music);
    Mix_FreeMusic(gameMusic);
    Mix_FreeChunk(StartSound);
    Mix_FreeChunk(JumpSound);
    Mix_FreeChunk(DeathSound);
    Mix_FreeChunk(seleteSound);
    Mix_FreeChunk(ClearSound);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_DestroyTexture(fish);
    SDL_DestroyTexture(startimg);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(fishgame);
    SDL_DestroyTexture(UI);
    SDL_DestroyTexture(fishselete);
    SDL_DestroyTexture(SetWindow);
    SDL_DestroyTexture(CheckConsole);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool gameover = false;

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
    bool ChangeOn = false;
    bool PauseBackgroundOnce = false;
    int AvatarState = 0;
    int y1 = 250;
    int x1 = 800;
    int x2 = 800;

    int Pos1 = -150;


    srand(time(NULL));
    int ThornOrderRandom = 0;

    SDL_Event event;
    int quit = 0;
    int Point = -1;

    SDL_Texture* font_Texture = SDL_CreateTextureFromSurface(Renderer, font_surface);

    //txt ���� ����
    //fp = fopen("data.txt", "w+");
    //if (fp == NULL) {
    //    printf("���Ͽ��� ����\n");
    //}
    //fprintf(fp, "%d\n%d", (Point < 0) ? 0 : Point, (!CoinNum) ? 0 : CoinNum);
    //fclose(fp);
    //��������Ʈ �ִϸ��̼� ������ ��ġ
    SDL_Rect rcSprite = { 0, 0, 100, 100 };
    SDL_Rect SpritePos = { 150, 250, 100, 100 };
    //��������Ʈ ��ġ
    // ��ֹ� ��������Ʈ �ִϸ��̼� ������ ��ġ
    SDL_Rect objSprite = { 0, 0, 100, 100 };
    //��ֹ� ��ġ
    SDL_Rect ThornPos = { 800, 250, 100, 100 };

    //���� ��������Ʈ �ִϸ��̼� ������ ��ġ
    SDL_Rect CoinSprite = {0, 0, 50, 50};

    //���� ��ġ
    SDL_Rect CoinPos = { 800, 200, 50, 50 };

    //��� ��������Ʈ �ִϸ��̼� ������ ��ġ
    SDL_Rect bgSprite = { 0, 0, 1024, 512 };
    SDL_Rect bgPos = { -550, -150, 1024, 512 };

    //�ְ� ���� ��� ��ġ
    SDL_Rect RecordPos = { 300, 10, 0, 0 };

    // ����Ʈ ��� ��Ʈ ��ġ
    SDL_Rect FontPos = { 30, 10, 0, 0 };
    SDL_Rect CoinFontPos = { 30, 50, 0, 0 };

    int fish_idx = 0;
    int fish_jump_idx = 0;
    int fish_state = 0;

    int AvatarSelete = 0;

    int Coin_idx = 0;

    int MAX_SPEED = 35;
    int MIN_SPEED = 15;

    int Obj_idx = 0;
    int ObjSpeed = 0;

    int CoinDistance;

    int Bgidx = 0;

    int Distance;
    int Dummy;

    bool isJumping = false;
    int jumpOffset = 0;
    int jumpDirection = 1;
    int jumpspeed = 20;
    int gravity = 1;
    int maxJumpHeight = 50;
    int CoinYRange;
    bool isFalling = false;
    bool ThornPassed = true;
    bool SpeedUp = false;
    bool Avatar = false;
    bool CoinPassed = false;
    bool CoinAte = false;
    bool AvatarStart = false;

    char PointText[20];
    char CoinText[20];
    int CoinRange = 0;

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

    //��ֹ� �̹��� �ε�
    Thorn = SDL_LoadBMP("Image/Game/Objects.bmp");
    if (Thorn == NULL) {
        printf("Failed to load Thorn image! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(background_surface);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
    
    BgSprite = SDL_LoadBMP("Image/Game/Background.bmp");
    if (BgSprite == NULL) {
        printf("Failed to load Thorn image! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(background_surface);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    InGameCoin = SDL_LoadBMP("Image/Game/Coin-Sheet.bmp");
    if (InGameCoin == NULL) {
        printf("Failed to load Thorn image! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(background_surface);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    //��ֹ� �̹��� ��� �����ϰ� �ϱ�
    SDL_SetColorKey(Thorn, SDL_TRUE, SDL_MapRGB(Thorn->format, 255, 0, 255));

    loadMedia();
    SDL_SetColorKey(Icon, SDL_TRUE, SDL_MapRGB(Icon->format, 255, 0, 255));
    SDL_SetColorKey(InGameCoin, SDL_TRUE, SDL_MapRGB(InGameCoin->format, 255, 0, 255));
    SDL_SetWindowIcon(window, Icon);
    SDL_FreeSurface(Icon);
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
                    if (seleteState > 3) {
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
                        seleteState = 3;
                    }
                    break;
                case SDLK_RIGHT:
                    if (Avatar == true) {
                        Mix_Volume(-1, SoundSetting);
                        Mix_PlayChannel(-1, seleteSound, 0);
                        AvatarSelete++;
                        if (AvatarSelete > 3)
                            AvatarSelete = 0;
                    }
                    break;
                case SDLK_LEFT:
                    if (Avatar == true) {
                        Mix_Volume(-1, SoundSetting);
                        Mix_PlayChannel(-1, seleteSound, 0);
                        AvatarSelete--;
                        if (AvatarSelete < 0)
                            AvatarSelete = 3;
                    }
                    break;
                case SDLK_SPACE:
                    if (gameStart == false && !Avatar) {
                        if (seleteState == 0) {
                            printf("���� ����!\n");
                            gameStart = true;
                            ClearRenderer = true;
                            Tutorial = true;
                        }
                        if (seleteState == 2) {
                            printf("����â\n");
                            SoundSetComplete = false;
                            SettingWindow = true;
                        }
                        if (seleteState == 3) {
                            printf("���� ����!\n");
                            close();
                        }
                        if (seleteState == 1) {
                            printf("�ƹ�Ÿ ����!\n");
                            Avatar = true;
                        }
                    }
                    break;
                case SDLK_z:
                    if (Tutorial == false) {
                        if (gameStart == true && SettingWindow == false) {
                            if (!isJumping && !isFalling) {
                                if (SoundOn == false) {
                                    Mix_Volume(-1, SoundSetting);
                                    Mix_PlayChannel(-1, JumpSound, 0);
                                    SoundOn = true;
                                }
                                isJumping = true;
                                jumpOffset = 0;
                                fish_state = 1;
                            }
                        }
                    }
                    if (Tutorial == true) {
                        break;
                    }
                    if (Avatar == true) {
                        switch (AvatarSelete)
                        {
                        case 0:
                            if (CoinNum >= 10) {
                                CoinNum -= 10;
                                //�ƹ�Ÿ ���� ȿ�� �ֱ�
                            }
                            else
                                printf("������ �����մϴ�!\n");
                            break;
                        case 1:
                            if (CoinNum >= 20) {
                                CoinNum -= 20;
                                //�ƹ�Ÿ ���� ȿ�� �ֱ�
                            }
                            else
                                printf("������ �����մϴ�!\n");
                            break;
                        case 2:
                            if (CoinNum >= 40) {
                                CoinNum -= 40;
                                //�ƹ�Ÿ ���� ȿ�� �ֱ�
                            }
                            else
                                printf("������ �����մϴ�!\n");
                            break;
                        }
                    }
                    break;
                }
            }
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_z:
                        if (isJumping) {
                            fish_state = 0;
                            isJumping = false;
                            isFalling = true;
                            SoundOn = false;
                        }

                }
            }
        }
        // �÷��̾� �̹��� �ε�
        switch (AvatarState)
        {
        case 0:
            player_surface = SDL_LoadBMP("Image/Game/fish_Padak-Sheet.bmp");
            break;
        case 1:
            player_surface = SDL_LoadBMP("Image/Game/fish_female-Sheet.bmp");
            break;
        case 2:
            player_surface = SDL_LoadBMP("Image/Game/Gold Fish-Sheet.bmp");
            break;
        case 3:
            player_surface = SDL_LoadBMP("Image/Game/While-Sheet.bmp");
            break;
        }
        //�÷��̾� �̹��� ��� �����ϰ� �ϱ�
        SDL_SetColorKey(player_surface, SDL_TRUE, SDL_MapRGB(player_surface->format, 255, 0, 255));
        if (player_surface == NULL) {
            printf("Failed to load player image! SDL Error: %s\n", SDL_GetError());
            SDL_FreeSurface(background_surface);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 0;
        }
        // ùȭ�� ����
        if (isDestroyed == false) {
            intro(Renderer, startimg);
            isDestroyed = true;
        }
        // ���� ȭ�� ����
        if (isDestroyed == true && gameStart == false && DeathMenu == false && SettingWindow == false && Avatar == false) {
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
            SDL_RenderCopy(Renderer, UI, NULL, NULL);
            switch (seleteState)
            {
            case 0:
                stretchTexture(Renderer, 170, 215, 80, 80, fish);
                break;
            case 1:
                stretchTexture(Renderer, 150, 265, 80, 80, fish);
                break;
            case 2:
                stretchTexture(Renderer, 130, 325, 80, 80, fish);
                break;
            case 3:
                stretchTexture(Renderer, 180, 375, 80, 80, fish);
                break;
            }
            SDL_RenderPresent(Renderer);
        }
        //�ƹ�Ÿ ���� ����
        if (isDestroyed == true && gameStart == false && DeathMenu == false && Avatar == true) {
            fp = fopen("data.txt", "r+");
            fscanf(fp, "%*[^\n]\n");
            fscanf(fp, "%d", &CoinNum);
            SDL_Texture* CoinTexture = SDL_CreateTextureFromSurface(Renderer, CoinFont_Surface);
            SDL_RenderClear(Renderer);
            SDL_RenderCopy(Renderer, background, NULL, NULL);
            SDL_RenderCopy(Renderer, Slot4, NULL, NULL);
            SDL_RenderCopy(Renderer, Slot3, NULL, NULL);
            SDL_RenderCopy(Renderer, Slot2, NULL, NULL);
            SDL_RenderCopy(Renderer, Slot1, NULL, NULL);
            snprintf(CoinText, sizeof(CoinText), "%d", CoinNum);
            CoinFont_Surface = TTF_RenderText_Blended(PointFont, CoinText, black);
            stretchTexture(Renderer, 510, 150, 85, 85, Skin1);
            stretchTexture(Renderer, 355, 150, 85, 85, Skin4);
            stretchTexture(Renderer, 205, 150, 85, 85, Skin3);
            stretchTexture(Renderer, 50, 150, 85, 85, Skin2);
            SDL_QueryTexture(CoinTexture, NULL, NULL, &RecordPos.w, &RecordPos.h);
            SDL_RenderCopy(Renderer, CoinTexture, NULL, &RecordPos);
            switch (AvatarSelete)
            {
            case 0:
                stretchTexture(Renderer, 50, 300, 80, 80, fish);
                break;
            case 1:
                stretchTexture(Renderer, 205, 300, 80, 80, fish);
                break;
            case 2:
                stretchTexture(Renderer, 355, 300, 80, 80, fish);
                break;
            case 3:
                stretchTexture(Renderer, 510, 300, 80, 80, fish);
                break;
            }
            fclose(fp);
            SDL_RenderPresent(Renderer);
            AvatarStart = true;
        }
        // ����â ����
        if (gameStart == false && DeathMenu == false && SettingWindow == true) {
            Setting(Renderer, background, SetWindow, CheckConsole);
            SoundSettingWindow();
            printf("\n���� ���� : %d\n", SoundSetting);
            printf("\nƩ�丮�� ���� ��� : %d\n", isTutorialoff);
            SoundSetComplete = true;
            SettingWindow = false;
        }
        // ���� ���� �� Ʃ�丮�� ����
        if (gameStart == true && DeathMenu == false && SettingWindow == false && Tutorial == true) {
            if (isTutorialoff == false) {
                Mix_PauseMusic(music);
                if (SoundOn == false) {
                    Mix_Volume(-1, SoundSetting);
                    Mix_PlayChannel(-1, StartSound, 0);
                    SoundOn = true;
                }
                SDL_RenderClear(Renderer);
                SDL_RenderCopy(Renderer, TutorialWindow, NULL, NULL);
                SDL_RenderPresent(Renderer);
                SDL_Delay(2000);
                char countdownText[20];
                SDL_Texture* font_Texture;
                SDL_Rect r = { 220, 370, 0, 0 };
                for (int i = 3; i > 0; i--) {
                    //��Ʈ �ؽ��Ŀ� ���ڸ� �ִ� �ڵ�
                    snprintf(countdownText, sizeof(countdownText), "Start in %d", i);
                    font_surface = TTF_RenderText_Blended(font, countdownText, color);
                    font_Texture = SDL_CreateTextureFromSurface(Renderer, font_surface);
                    SDL_QueryTexture(font_Texture, NULL, NULL, &r.w, &r.h);

                    //������ ������Ʈ �Լ�
                    SDL_RenderClear(Renderer);
                    SDL_RenderCopy(Renderer, TutorialWindow, NULL, NULL);
                    SDL_RenderCopy(Renderer, font_Texture, NULL, &r);
                    SDL_RenderPresent(Renderer);
                    SDL_Delay(1000);

                    SDL_FreeSurface(font_surface);
                    SDL_DestroyTexture(font_Texture);
                }
            }
            Tutorial = false;
            SoundOn = false;
        }
        // ���� �۵� ����
        // ���� ���� �� �������� ������� ���� -> Texture�� �ƴ� Surface�� ����
        if (gameStart == true && DeathMenu == false && SettingWindow == false && Tutorial == false && gameover == false) {
            fp = fopen("data.txt", "r");
            // ù ��° ���� ���ڿ��� ����
            fscanf(fp, "%d", &Dummy);
            fscanf(fp, "%*[^\n]\n");
            fscanf(fp, "%d", &CoinNum);
            fclose(fp);
            //ó�� �������� �� ��ġ �ʱ�ȭ
            if (ClearRenderer == true) {
                MAX_SPEED = 35;
                MIN_SPEED = 15;
                SDL_RenderClear(Renderer);
                SDL_RenderPresent(Renderer);
                Mix_Volume(-1, SoundSetting);
                Mix_PlayMusic(gameMusic, -1);
                ThornPassed = true;
                CoinPassed = true;
                Point = -1;
                SpritePos.y = 250;
                ClearRenderer = false;
            }
            //��ֹ��� �������� �� ��ġ �ʱ�ȭ �� ���� �߰�
            if (ThornPassed == true) {
                ObjSpeed = rand() % (MAX_SPEED - MIN_SPEED + 1) + MIN_SPEED;
                ++Point;
                ThornOrderRandom = rand() % 51;
                if (ThornOrderRandom > 2 && ThornOrderRandom != 50)
                    ThornOrderRandom = rand() % 3;
                SpeedUp = false;
                ThornPassed = false;
            }
            //������ �������� �� ��ġ �ʱ�ȭ
            if (CoinPassed == true) {
                CoinAte = false;
                CoinRange = rand() % (800 - 500 + 1) + 500;
                x2 = x2 + CoinRange;
                CoinYRange = rand() % (300 - 200 + 1) + 200;
                CoinPos.y = CoinYRange;
                CoinPassed = false;
            }
            //������ �Ծ��� �� ��ġ �ʱ�ȭ �� ���� �߰�
            if (CoinAte == true) {
                ++CoinNum;
                FILE *fp_write = fopen("data.txt", "w+");
                fscanf(fp_write, "%d", &Dummy);
                fscanf(fp_write, "%*[^\n]\n");
                fprintf(fp_write, "%d\n%d", Dummy, CoinNum);
                fclose(fp_write);
                CoinAte = false;
            }
            Distance = calculateDistance(SpritePos, ThornPos);
            CoinDistance = calculateDistance(SpritePos, CoinPos);
            if (Distance < 70) {
                printf("�׾����ϴ�! ");
                gameover = true;
            }
            if (CoinDistance < 70) {
                Mix_Volume(-1, SoundSetting);
                Mix_PlayChannel(-1, CoinSound, 0);
                CoinRange = rand() % (800 - 500 + 1) + 500;
                x2 = x2 + CoinRange;
                CoinYRange = rand() % (300 - 200 + 1) + 200;
                CoinPos.y = CoinYRange;
                CoinAte = true;
            }
            if (Point % 10 == 0 && Point != 0 && SpeedUp == false) {
                MAX_SPEED += 3;
                MIN_SPEED += 3;
                Mix_Volume(-1, SoundSetting);
                Mix_PlayChannel(-1, ClearSound, 0);
                SpeedUp = true;
            }
            snprintf(PointText, sizeof(PointText), "%d", Point);
            snprintf(CoinText, sizeof(CoinText), "%d", CoinNum);
            Point_surface = TTF_RenderText_Blended(PointFont, PointText, black);
            CoinFont_Surface = TTF_RenderText_Blended(PointFont, CoinText, black);
            Coin_idx++;
            Obj_idx++;
            fish_idx++;
            Bgidx++;
            bgSprite.x = 1024 * Bgidx;
            objSprite.x = 100 * Obj_idx;
            if (ThornOrderRandom == 50) {
                objSprite.y = 100 * 3;
            }
            else {
                objSprite.y = 100 * ThornOrderRandom;
            }
            rcSprite.x = 100 * fish_idx;
            rcSprite.y = 100 * fish_state;
            CoinSprite.x = 50 * Coin_idx;
            if (fish_idx >= 7)
                fish_idx = 0;
            if (Obj_idx >= 7)
                Obj_idx = 0;
            if (Coin_idx >= 7)
                Coin_idx = 0;
            if (Bgidx >= 9) {
                Bgidx = 0;
            }
            //���¿� �°� �ִϸ��̼� ���ϴ� if��
            if (isJumping || isFalling) {
                fish_jump_idx++;
                rcSprite.y = 100 * fish_state;
                rcSprite.x = 100 * fish_jump_idx;
                if (fish_jump_idx >= 5)
                    fish_jump_idx = 0;
            }
            //���� ������ �� y�� ����
            if (isJumping) {
                jumpOffset -= jumpspeed;
                jumpspeed -= gravity;
            }
            //�������� ������ �� y�� ����
            else if (isFalling) {
                jumpOffset += jumpspeed;
                jumpspeed += gravity;
                fish_state = 1;
                if (jumpOffset >= 0) {
                    jumpOffset = 0;
                    isFalling = false;
                    fish_state = 0;
                }
            }
            //���� ���� ���� ���ǹ�
            if (jumpOffset < -150) {
                jumpOffset = -150;
            }
            else if (jumpOffset > 150) {
                jumpOffset = 150;
            }
            //������ y���� �������� ����
            bgPos.x = Pos1;
            if (ChangeOn == false) {
                Pos1 -= 1;
                if (Pos1 < -250) {
                    ChangeOn = true;
                }
            }
            if (ChangeOn == true) {
                Pos1 += 1;
                if (Pos1 > -50) {
                    ChangeOn = false;
                }
            }
            SpritePos.y = 250 + jumpOffset;
            ThornPos.x = x1;
            CoinPos.x = x2;
            x1 -= ObjSpeed;
            x2 -= 20;
            if (x1 <= -100) {
                x1 = 800;
                ThornPassed = true;
            }
            if (x2 <= -100) {
                x2 = 800;
                CoinPassed = true;
            }
            // ��ֹ��� ȭ�� ���� ���� ����� �ٽ� ȭ�� ������ ������ �̵�
            SDL_BlitSurface(BgSprite, &bgSprite, window_surface, &bgPos);
            SDL_BlitSurface(player_surface, &rcSprite, window_surface, &SpritePos);
            SDL_BlitSurface(Thorn, &objSprite, window_surface, &ThornPos);
            SDL_BlitSurface(Point_surface, NULL, window_surface, &FontPos);
            SDL_BlitSurface(CoinFont_Surface, NULL, window_surface, &CoinFontPos);
            SDL_BlitSurface(InGameCoin, &CoinSprite, window_surface, &CoinPos);
            //ȭ�� ������Ʈ
            SDL_UpdateWindowSurface(window);
            SDL_Delay(100);
        }
        //���� ���� ����
        if (gameover == true) {
            x1 = 800;
            ThornPos.x = x1;
            Mix_PauseMusic(gameMusic);
            // ��ŷ �ο�
            if (Point == 0)
                Rate = TTF_RenderText_Blended(YourRateis, "FFF", Red);
            else if (Point < 10)
                Rate = TTF_RenderText_Blended(YourRateis, "F", Red);
            else if (Point >= 10 && Point < 20)
                Rate = TTF_RenderText_Blended(YourRateis, "E", Red);
            else if (Point >= 20 && Point < 30)
                Rate = TTF_RenderText_Blended(YourRateis, "D", Blue);
            else if (Point >= 30 && Point < 40)
                Rate = TTF_RenderText_Blended(YourRateis, "C", Blue);
            else if (Point >= 40 && Point < 50)
                Rate = TTF_RenderText_Blended(YourRateis, "B", Pink);
            else if (Point >= 50 && Point < 80)
                Rate = TTF_RenderText_Blended(YourRateis, "A", Pink);
            else if (Point >= 80)
                Rate = TTF_RenderText_Blended(YourRateis, "S", Pink);
            if (ThornOrderRandom == 50) {
                Rate = TTF_RenderText_Blended(YourRateis, "?", black);
            }
            //�浹�� ��ֹ��� ���� ���� ���� ȭ�� �ٸ��� ���
            if (DeathMenu == false) {
                Mix_Volume(-1, SoundSetting);
                Mix_PlayChannel(-1, DeathSound, 0);
                DeathMenu = true;
            }
            if (ThornOrderRandom == 0) {
                GameOver = SDL_LoadBMP("Image/Game/gameover1.bmp");
                if (GameOver == NULL) {
                    printf("�̹��� ���� �ҷ��� �� ����!\n");
                    close();
                }
            }
            if (ThornOrderRandom == 1) {
                GameOver = SDL_LoadBMP("Image/Game/gameover2.bmp");
                if (GameOver == NULL) {
                    printf("�̹��� ���� �ҷ��� �� ����!\n");
                    close();
                }
            }
            if (ThornOrderRandom == 2) {
                GameOver = SDL_LoadBMP("Image/Game/gameover3.bmp");
                if (GameOver == NULL) {
                    printf("�̹��� ���� �ҷ��� �� ����!\n");
                    close();
                }
            }
            if (ThornOrderRandom == 50) {
                GameOver = SDL_LoadBMP("Image/Game/gameover4.bmp");
                if (GameOver == NULL) {
                    printf("�̹��� ���� �ҷ��� �� ����!\n");
                    close();
                }
            }
            //���� ���ڿ� ����
            char PointValue[20];
            char RecrodValue[20];
            SDL_Surface* RecordValueSurface = NULL;
            SDL_Texture* RecordValueTexture = NULL;
            SDL_Surface* GameoverPoint = NULL;
            SDL_Texture* GameoverPointTexture = NULL;
            SDL_Texture* YourRateisTexture = NULL;
            SDL_Texture* YourRateisNTexture = NULL;
            SDL_Rect p = { 400, 350, 0, 0 };
            SDL_Rect RatePos = { 450, 230, 0, 0 };
            SDL_Rect YRIPos = { 350, 200, 0, 0 };
            //������ �ؽ��ķ� ��ȯ
            SDL_Texture* gameoverScreen = SDL_CreateTextureFromSurface(Renderer, GameOver);
            SDL_FreeSurface(GameOver);
            SDL_RenderCopy(Renderer, gameoverScreen, NULL, NULL);
            SDL_RenderPresent(Renderer);
            fp = fopen("data.txt", "r");
            if (fp == NULL) {
                printf("���Ͽ��� ����\n");
            }
            else {
                fscanf(fp, "%d", &NewRecord);
                fclose(fp);
            }
            fp = fopen("data.txt", "w+");
            if (fp == NULL) {
                printf("���� ���� ����!\n");
            }
            else {
                fprintf(fp, "%d\n%d", (Point <= 0) ? 0 : (Point >= NewRecord) ? Point : NewRecord, (!CoinNum) ? 0 : CoinNum);
                fclose(fp);
            }
            //����Ʈ ���� ����
            snprintf(PointValue, sizeof(PointValue), "Point : %d", Point);
            GameoverPoint = TTF_RenderText_Blended(countFont, PointValue, black);
            GameoverPointTexture = SDL_CreateTextureFromSurface(Renderer, GameoverPoint);
            //���� ����� ���� ����
            YRI = TTF_RenderText_Blended(YRIN, "Your Rate is...", black);
            YourRateisNTexture = SDL_CreateTextureFromSurface(Renderer, YRI);
            YourRateisTexture = SDL_CreateTextureFromSurface(Renderer, Rate);
            //�ְ� ���� ����
            snprintf(RecrodValue, sizeof(RecrodValue), "Record : %d", NewRecord < Point ? Point : NewRecord);
            RecordValueSurface = TTF_RenderText_Blended(Record, RecrodValue, black);
            RecordValueTexture = SDL_CreateTextureFromSurface(Renderer, RecordValueSurface);
            
            //�ؽ��� ���
            SDL_QueryTexture(GameoverPointTexture, NULL, NULL, &p.w, &p.h);
            SDL_QueryTexture(YourRateisNTexture, NULL, NULL, &YRIPos.w, &YRIPos.h);
            SDL_QueryTexture(YourRateisTexture, NULL, NULL, &RatePos.w, &RatePos.h);
            SDL_QueryTexture(RecordValueTexture, NULL, NULL, &RecordPos.w, &RecordPos.h);
            SDL_RenderCopy(Renderer, GameoverPointTexture, NULL, &p);
            SDL_RenderCopy(Renderer, YourRateisTexture, NULL, &RatePos);
            SDL_RenderCopy(Renderer, YourRateisNTexture, NULL, &YRIPos);
            SDL_RenderCopy(Renderer, RecordValueTexture, NULL, &RecordPos);
            SDL_FreeSurface(GameoverPoint);
            SDL_FreeSurface(YRI);
            SDL_FreeSurface(Rate);
            SDL_FreeSurface(RecordValueSurface);
            SDL_RenderPresent(Renderer);
            SDL_DestroyTexture(GameoverPointTexture);
            SDL_DestroyTexture(YourRateisTexture);
            SDL_DestroyTexture(YourRateisNTexture);
            SDL_DestroyTexture(gameoverScreen);
            SDL_DestroyTexture(RecordValueTexture);
            printf("  ���� : %d\n", Point);
            SDL_Delay(4000);
            gameover = false;
            DeathMenu = false;
            gameStart = false;
            MusicStart = false;
            ClearRenderer = true;
        }
    }
    
    close();
    return 0;
}
