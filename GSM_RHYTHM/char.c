#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "Example.h"

SDL_Window* window = NULL;
SDL_Surface* window_surface = NULL;
SDL_Surface* player_surface = NULL;
SDL_Surface* background_surface = NULL;

int main(void) {
    // SDL �ʱ�ȭ
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL �ʱ�ȭ�� �����߽��ϴ�! SDL Error: %s\n", SDL_GetError());
        return -1;
    }

    // SDL â ����
    window = SDL_CreateWindow("Sprite Add", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL â�� �������� ���߽��ϴ�! SDL Error : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // â ǥ�� ��������
    window_surface = SDL_GetWindowSurface(window);
    if (window_surface == NULL) {
        printf("â ǥ���� �������� ���߽��ϴ�! SDL Error : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // ��� �̹��� �ε�
    background_surface = SDL_LoadBMP("Image/Player/background.bmp");
    if (background_surface == NULL) {
        printf("��� �̹����� �ε����� ���߽��ϴ�! SDL Error : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // �÷��̾� �̹��� �ε� �� ���� Ű ����
    player_surface = SDL_LoadBMP("Image/Player/Player-test-sheet.bmp");
    if (player_surface == NULL) {
        printf("�÷��̾� �̹����� �ε����� ���߽��ϴ�! SDL Error : %s\n", SDL_GetError());
        SDL_FreeSurface(background_surface);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_SetColorKey(player_surface, SDL_TRUE, SDL_MapRGB(player_surface->format, 255, 0, 255));

    // �ʱ� �ִϸ��̼� ���� ����
    SDL_Rect rcSprite = { 0, 0, 64, 44 };
    int player_idx = 0;
    int player_atk_idx = 0;
    int player_state = 0;
    bool player_move = false;
    bool player_idle = true;
    int DelaySec = 100;

    // �̺�Ʈ ����
    int quit = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    player_state = 1;
                    player_move = true;
                    player_idle = false;
                    break;
                case SDLK_RIGHT:
                    player_move = true;
                    player_idle = false;
                    player_state = 1;
                    break;
                }
            }
            if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    player_move = false;
                    player_idle = true;
                    player_state = 0;
                    break;
                case SDLK_RIGHT:
                    player_move = false;
                    player_idle = true;
                    player_state = 0;
                    break;
                }
            }
        }

        // �ִϸ��̼� ������Ʈ
        if (player_idle == true && player_move == false) {
            player_idx++;
            rcSprite.x = 64 * player_idx;
            if (player_idx >= 5)
                player_idx = 0;
            rcSprite.y = 44 * player_state;
        }
        if (player_move == true && player_idle == false) {
            rcSprite.x = 64 * player_atk_idx;
            player_atk_idx++;
            if (player_atk_idx >= 8)
                player_atk_idx = 0;
            rcSprite.y = 44 * player_state;
        }

        // ��� �̹����� â ǥ�鿡 �׸���
        SDL_BlitSurface(background_surface, NULL, window_surface, NULL);

        // �÷��̾� �̹����� â ǥ�鿡 �׸���
        SDL_BlitSurface(player_surface, &rcSprite, window_surface, NULL);

        // â ������Ʈ
        SDL_UpdateWindowSurface(window);

        // �ִϸ��̼� �ӵ� ���� (������)
        SDL_Delay(DelaySec);  // �� 10 �����Ӵ� 1���� �ӵ�
    }

    // �ڿ� ���� �� SDL ����
    SDL_FreeSurface(player_surface);
    SDL_FreeSurface(background_surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
