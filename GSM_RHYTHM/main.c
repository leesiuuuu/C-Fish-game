#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>    
#include "Example.h"
#include <SDL_mixer.h>

SDL_Window* window = NULL;
SDL_Renderer* Renderer = NULL;
SDL_Texture* Texture = NULL;
TTF_Font* Font = NULL;
//���� ȭ�� UI ���� �ؽ���
SDL_Texture* UITexture = NULL;
SDL_Texture* UITexture2 = NULL;
SDL_Texture* UITexture3 = NULL;
//����� ��� ������
Mix_Chunk* moveAudio = NULL;
Mix_Music* music = NULL;
Mix_Chunk* seleteAudio = NULL;
//�� ���� ȭ�� UI ���� �ؽ���
SDL_Texture* UITex1 = NULL;
SDL_Texture* UITex2 = NULL;
SDL_Texture* UITex3 = NULL;

bool AudioSound(){
    moveAudio = Mix_LoadWAV("Sound/select.wav");
    if (!moveAudio) {
        printf("����� �ε忡 �����߽��ϴ�! SDL_Mix Error : %s\n", Mix_GetError());
        return false;
    }
    seleteAudio = Mix_LoadWAV("Sound/selected.wav");
    if (!seleteAudio) {
        printf("����� �ε忡 �����߽��ϴ�! SDL_Mix Error : %s\n", Mix_GetError());
        return false;
    }
    return true;
}

int selectedButtonIndex = 0;
int musicSelectedButtenIndex = 0;
bool startToggle = false;
void handleKeyPress(SDL_Event event) {
    AudioSound();
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
            // ���õ� ��ư �ε����� ���ҽ�Ŵ
            Mix_PlayChannel(-1, moveAudio, 0);
            selectedButtonIndex--;
            if (selectedButtonIndex < 0) {
                selectedButtonIndex = 2; // ������ ��ư���� �̵�
            }
            printf("���� ȭ��ǥ Ű�� ���Ƚ��ϴ�. %d\n", selectedButtonIndex);
            break;
        case SDLK_DOWN:
            Mix_PlayChannel(-1, moveAudio, 0);
            // ���õ� ��ư �ε����� ������Ŵ
            selectedButtonIndex++;
            if (selectedButtonIndex > 2) {
                selectedButtonIndex = 0; // ù ��° ��ư���� �̵�
            }
            printf("�Ʒ��� ȭ��ǥ Ű�� ���Ƚ��ϴ�.%d\n", selectedButtonIndex);
            break;
        case SDLK_LEFT:
            printf("���� ȭ��ǥ Ű�� ���Ƚ��ϴ�.\n");
            break;
        case SDLK_RIGHT:
            printf("������ ȭ��ǥ Ű�� ���Ƚ��ϴ�.\n");
            break;
        case SDLK_SPACE:
            printf("�����̽��ٰ� ���Ƚ��ϴ�.\n");
            if (selectedButtonIndex == 2)
            {
                printf("���α׷� ����!\n");
                SDL_Quit();
            }
            else if (selectedButtonIndex == 0) {
                Mix_PlayChannel(-1, seleteAudio, 0);
                SDL_Delay(500);
                printf("���� ����!\n");
                startToggle = true;
            }
                
            else if (selectedButtonIndex == 1)
                printf("�ɼ� ���� ����\n");
            
            break;
            // �ʿ��� Ű�� ���� �߰� ó���� ���⿡ �߰��� �� �ֽ��ϴ�.
        default:
            break;
        }
    }
}

//SDL �ʱ�ȭ
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL �ʱ�ȭ ����! SDL Error : %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf �ʱ�ȭ ����! SDL_ttf Error : %s\n", TTF_GetError());
        return false;
    }

    window = SDL_CreateWindow("Rhythm Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
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

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
        printf("SDL_image�� �ʱ�ȭ�� �� �����ϴ�! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer �ʱ�ȭ�� �����߽��ϴ�! SDL_Mixer Error : %s\n", Mix_GetError());
        return false;
    }

    return true;
}

bool seletemain() {
    stretchTexture(Renderer, 200, 100, 230, 150, UITex1);
    stretchTexture(Renderer, 200, 200, 230, 150, UITex2);
    stretchTexture(Renderer, 200, 300, 230, 150, UITex3);
    return true;
}

bool loadMedia() {
    Texture = IMG_LoadTexture(Renderer, "Image/main.png");
    UITexture = IMG_LoadTexture(Renderer, "Image/startbutton.png");
    UITexture2 = IMG_LoadTexture(Renderer, "Image/optionbutton.png");
    UITexture3 = IMG_LoadTexture(Renderer, "Image/exitbutton.png");
    music = Mix_LoadMUS("Songs/MainSong.wav");
    UITex1 = IMG_LoadTexture(Renderer, "Image/DynamiteSongName.png");

    // ���õ� ��ư�� ���� �ؽ�ó �ʱ�ȭ
    switch (selectedButtonIndex) {
    case 0:
        UITexture = IMG_LoadTexture(Renderer, "Image/startbuttonselected.png");
        break;
    case 1:
        UITexture2 = IMG_LoadTexture(Renderer, "Image/optionbuttonselected.png");
        break;
    case 2:
        UITexture3 = IMG_LoadTexture(Renderer, "Image/exitbuttonselected.png");
        break;
    }

    switch (startToggle)
    {
    case true:
        Texture = IMG_LoadTexture(Renderer, "Image/selectMain.png");
        SDL_DestroyTexture(UITexture);
        SDL_DestroyTexture(UITexture2);
        SDL_DestroyTexture(UITexture3);

        
        break;
    }

    if (!music) {
        printf("���� ������ �ҷ��� �� �����ϴ�! SDL_Mixer Error: %s\n", Mix_GetError());
        return false;
    }
    Texture_Check(Texture);
    Texture_Check(UITexture);
    Texture_Check(UITexture2);
    Texture_Check(UITexture3);
    Texture_Check(UITex1);
    //Texture_Check(UITex2);
    //Texture_Check(UITex3);
    return true;
}

void close() {
    SDL_DestroyTexture(Texture);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    window = NULL;
    Renderer = NULL;
    Texture = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!init()) {
        printf("SDL �ʱ�ȭ�� �����Ͽ����ϴ�!\n");
        return -1;
    }

    if (!loadMedia()) {
        printf("�̵�� �ε��� �����Ͽ����ϴ�!\n");
        close();
        return -1;
    }
    Mix_PlayMusic(music, -1);
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            handleKeyPress(event);
        }        
        loadMedia();
        SDL_RenderClear(Renderer);
        SDL_RenderCopy(Renderer, Texture, NULL, NULL);
        stretchTexture(Renderer, 200, 100, 230, 150, UITexture);
        stretchTexture(Renderer, 200, 200, 230, 150, UITexture2);
        stretchTexture(Renderer, 200, 300, 230, 150, UITexture3);   
        SDL_RenderPresent(Renderer);
    }

    close();
    return 0;
}
