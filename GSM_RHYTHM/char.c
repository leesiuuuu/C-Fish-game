#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "Example.h"

SDL_Window* window = NULL;
SDL_Surface* window_surface = NULL;
SDL_Surface* player_surface = NULL;
SDL_Surface* background_surface = NULL;

int main(void) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 초기화에 실패했습니다! SDL Error: %s\n", SDL_GetError());
        return -1;
    }

    // SDL 창 생성
    window = SDL_CreateWindow("Sprite Add", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL 창을 생성하지 못했습니다! SDL Error : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // 창 표면 가져오기
    window_surface = SDL_GetWindowSurface(window);
    if (window_surface == NULL) {
        printf("창 표면을 가져오지 못했습니다! SDL Error : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // 배경 이미지 로드
    background_surface = SDL_LoadBMP("Image/Player/background.bmp");
    if (background_surface == NULL) {
        printf("배경 이미지를 로드하지 못했습니다! SDL Error : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // 플레이어 이미지 로드 및 색상 키 설정
    player_surface = SDL_LoadBMP("Image/Player/Player-test-sheet.bmp");
    if (player_surface == NULL) {
        printf("플레이어 이미지를 로드하지 못했습니다! SDL Error : %s\n", SDL_GetError());
        SDL_FreeSurface(background_surface);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_SetColorKey(player_surface, SDL_TRUE, SDL_MapRGB(player_surface->format, 255, 0, 255));

    // 초기 애니메이션 상태 설정
    SDL_Rect rcSprite = { 0, 0, 64, 44 };
    int player_idx = 0;
    int player_atk_idx = 0;
    int player_state = 0;
    bool player_move = false;
    bool player_idle = true;
    int DelaySec = 100;

    // 이벤트 루프
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

        // 애니메이션 업데이트
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

        // 배경 이미지를 창 표면에 그리기
        SDL_BlitSurface(background_surface, NULL, window_surface, NULL);

        // 플레이어 이미지를 창 표면에 그리기
        SDL_BlitSurface(player_surface, &rcSprite, window_surface, NULL);

        // 창 업데이트
        SDL_UpdateWindowSurface(window);

        // 애니메이션 속도 조절 (딜레이)
        SDL_Delay(DelaySec);  // 약 10 프레임당 1초의 속도
    }

    // 자원 해제 및 SDL 종료
    SDL_FreeSurface(player_surface);
    SDL_FreeSurface(background_surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
