#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <cJSON.h>
#include <SDL_image.h>
#include "Example.h"
#include <SDL_audio.h>
#include "osuToC.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define NOTE_SPEED 5

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Mix_Music *music = NULL;
bool isRunning = true;
    
//스코어 변수
int score = 0;

// 노트의 위치
int noteY1 = 0; // 시작 위치
int noteY2 = 0; // 시작 위치
int noteY3 = 0; // 시작 위치
int noteY4 = 0; // 시작 위치

int noteJudge = 0;

bool keyCheck[4] = { false, false, false, false };
bool NoteCheck[4] = { false, false, false, false };

int combo = 0;


void handleKeyPress(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_d:
            printf("1번이 눌렸습니다.\n");
            keyCheck[0] = true;
            break;
        case SDLK_f:
            printf("2번이 눌렸습니다.\n");
            keyCheck[1] = true;
            break;
        case SDLK_j:
            printf("3번이 눌렸습니다.\n");
            keyCheck[2] = true;
            break;
        case SDLK_k:
            printf("4번이 눌렸습니다.\n");
            keyCheck[3] = true;
            break;
            // 필요한 키에 대한 추가 처리를 여기에 추가할 수 있습니다.
        default:
            keyCheck[0] = false;
            keyCheck[1] = false;
            keyCheck[2] = false;
            keyCheck[3] = false;
            break;
        }
    }
}

// 거리 계산 함수
double calculateDistance(SDL_Rect noteRect, SDL_Rect noteCheck) {
    // 노트의 중심 좌표 계산
    double noteCenterX = noteRect.x + noteRect.w / 2;
    double noteCenterY = noteRect.y + noteRect.h / 2;

    // 노트 확인 도형의 중심 좌표 계산
    double noteCheckCenterX = noteCheck.x + noteCheck.w / 2;
    double noteCheckCenterY = noteCheck.y + noteCheck.h / 2;

    // 두 점 사이의 거리 계산
    double distance = sqrt(pow(noteCenterX - noteCheckCenterX, 2) + pow(noteCenterY - noteCheckCenterY, 2));
    return distance;
}

// 판정 함수
void FunctionOnDistance(SDL_Rect noteRect, SDL_Rect noteCheck, int *noteY) {
    // 노트와 노트 확인 도형 사이의 거리 계산
    double distance = calculateDistance(noteRect, noteCheck);

    // 거리에 따라 색상 변경
    if (distance < 40) {
        printf("Perfect\n");
        score += 200;
        printf("내려오는데 걸린 시간 : %d ms\n", SDL_GetTicks());
        printf("스코어 : %d\n", score);
        ++combo;
        *noteY = -100;
        noteJudge = 4;
    }
    else if(distance < 60) {
        printf("great\n");
        score += 100;
        *noteY = -100;
        noteJudge = 3;
        ++combo;
    }
    else if (distance < 70) {
        printf("good\n");
        score += 50;
        *noteY = -100;
        noteJudge = 2;
        combo = 0;
    }
    else if (distance < 0 && distance > -60) {
        printf("great\n");
        score += 100;
        *noteY = -100;
        noteJudge = 3;
        ++combo;
    }
    else if (distance > -60 && distance < -70) {
        printf("good\n");
        score += 50;
        *noteY = -100;
        noteJudge = 2;
        combo = 0;
    }
    else {
        printf("miss!\n");
        score -= 100;
        noteJudge = 1;
        combo = 0;
    }
}

// SDL 초기화 함수
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL 초기화 실패: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Note Falling", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("윈도우 생성 실패: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("렌더러 생성 실패: %s\n", SDL_GetError());
        return false;
    }

    SDL_Init(SDL_INIT_AUDIO);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer 초기화에 실패했습니다! SDL_Mixer Error : %s\n", Mix_GetError());
        return false;
    }


    return true;
}

// SDL 종료 함수
void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


// 노트를 그리는 함수
void drawNote() {
    //이미지 로드 포인터 변수
    SDL_Texture* perfectJudge = IMG_LoadTexture(renderer, "Image/perfect.png");
    SDL_Texture* greatJudge = IMG_LoadTexture(renderer, "Image/great.png");
    SDL_Texture* goodJudge = IMG_LoadTexture(renderer, "Image/good.png");
    SDL_Texture* missJudge = IMG_LoadTexture(renderer, "Image/miss.png");
    SDL_SetTextureAlphaMod(perfectJudge, 50);
    SDL_SetTextureAlphaMod(greatJudge, 50);
    SDL_SetTextureAlphaMod(goodJudge, 50);
    SDL_SetTextureAlphaMod(missJudge, 50);
  

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 검은색 배경
    SDL_RenderClear(renderer);

    // 노트를 빨간색으로 그림
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //노트 위치, 크기 코드    
    SDL_Rect noteRect1 = {10, noteY1, 60, 20}; 
    SDL_RenderFillRect(renderer, &noteRect1);
    /*

    
    SDL_Rect noteRect2 = { 70, noteY2, 60, 20 };
    SDL_RenderFillRect(renderer, &noteRect2);

    SDL_Rect noteRect3 = { 130, noteY3, 60, 20 };
    SDL_RenderFillRect(renderer, &noteRect3);

    SDL_Rect noteRect4 = { 190, noteY4, 60, 20 };
    SDL_RenderFillRect(renderer, &noteRect4);

    SDL_Rect noteRect01 = { 10, noteY01, 60, 20 };
    SDL_RenderFillRect(renderer, &noteRect01);

    SDL_Rect noteRect02 = { 70, noteY02, 60, 20 };
    SDL_RenderFillRect(renderer, &noteRect02);

    SDL_Rect noteRect03 = { 130, noteY03, 60, 20 };
    SDL_RenderFillRect(renderer, &noteRect03);

    SDL_Rect noteRect04 = { 190, noteY04, 60, 20 };
    SDL_RenderFillRect(renderer, &noteRect04);
    */


    //확인 도형을 하얀색으로 그림
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    

    //노트 확인 도형
    SDL_Rect noteCheck1 = { 10, 400, 60, 20 };
    SDL_RenderFillRect(renderer, &noteCheck1);

    SDL_Rect noteCheck2 = { 70, 400, 60, 20 };
    SDL_RenderFillRect(renderer, &noteCheck2);

    SDL_Rect noteCheck3 = { 130, 400, 60, 20 };
    SDL_RenderFillRect(renderer, &noteCheck3);
 
    SDL_Rect noteCheck4 = { 190, 400, 60, 20 };
    SDL_RenderFillRect(renderer, &noteCheck4);

    //판정 이미지 출력
    switch (noteJudge)
    {
    case 1:
        SDL_DestroyTexture(goodJudge);
        SDL_DestroyTexture(perfectJudge);
        SDL_DestroyTexture(greatJudge);
        stretchTexture(renderer, 50, 100, 150, 100, missJudge);
        break;
    case 2:
        SDL_DestroyTexture(missJudge);
        SDL_DestroyTexture(perfectJudge);
        SDL_DestroyTexture(greatJudge);
        stretchTexture(renderer, 50, 100, 150, 100, goodJudge);
        break;
    case 3:
        SDL_DestroyTexture(missJudge);
        SDL_DestroyTexture(perfectJudge);
        SDL_DestroyTexture(goodJudge);
        stretchTexture(renderer, 50, 100, 150, 100, greatJudge);
        break;
    case 4:
        SDL_DestroyTexture(missJudge);
        SDL_DestroyTexture(goodJudge);
        SDL_DestroyTexture(greatJudge);
        stretchTexture(renderer, 50, 100, 150, 100, perfectJudge);
        break;
    }
    if (keyCheck[0] == true) {
        FunctionOnDistance(noteRect1, noteCheck1, &noteY1);
        keyCheck[0] = false;
    }
    //키 눌렸을 시 판정 확인
    /*

    if (keyCheck[1] == true) {
        if (calculateDistance(noteRect2, noteCheck2) > calculateDistance(noteRect02, noteCheck2)) {
            FunctionOnDistance(noteRect02, noteCheck2, &noteY02);
        }
        else {
            FunctionOnDistance(noteRect2, noteCheck2, &noteY2);
        }
        keyCheck[1] = false;
    }
    if (keyCheck[2] == true) {
        if (calculateDistance(noteRect3, noteCheck3) > calculateDistance(noteRect03, noteCheck3)) {
            FunctionOnDistance(noteRect02, noteCheck2, &noteY03);
        }
        else {
            FunctionOnDistance(noteRect3, noteCheck3, &noteY3);
        }
        keyCheck[2] = false;
    }
    if (keyCheck[3] == true) {
        if (calculateDistance(noteRect4, noteCheck4) > calculateDistance(noteRect04, noteCheck4)) {
            FunctionOnDistance(noteRect04, noteCheck4, &noteY04);
        }
        else {
            FunctionOnDistance(noteRect4, noteCheck4, &noteY4);
        }
        keyCheck[3] = false;
    }
    */


    //겉 라인 생성 코드
    SDL_RenderDrawLine(renderer, 10, 2, 10, 500);
    SDL_RenderDrawLine(renderer, 250, 2, 250, 500);
    //속 라인 생성 코드
    SDL_RenderDrawLine(renderer, 70, 2, 70, 500);
    SDL_RenderDrawLine(renderer, 130, 2, 130, 500);
    SDL_RenderDrawLine(renderer, 190, 2, 190, 500);

    SDL_RenderPresent(renderer);
}

bool LoadMedia() {
    music = Mix_LoadMUS("Songs/Insert Coin.wav");

    if (!music) {
        printf("음악 파일을 불러올 수 없습니다! SDL_Mixer Error: %s\n", Mix_GetError());
        return false;
    }
    return true;
}

// 노트 이동 함수
//노트가 노트 체크 부분에 다다르는 시간 : 1.3s
void moveNote1() {
    noteY1 += NOTE_SPEED;
    if (noteY1 > SCREEN_HEIGHT) {
        // 화면 밑으로 나가면 초기 위치로 리셋
        noteY1 = -100;
        printf("miss!\n");
        noteJudge = 1;
    }
}
void moveNote2() {
    noteY2 += NOTE_SPEED;

    if (noteY2 > SCREEN_HEIGHT) {
        // 화면 밑으로 나가면 초기 위치로 리셋
        noteY2 = -100;
        printf("miss!\n");
        noteJudge = 1;
    }

}
void moveNote3() {
    noteY3 += NOTE_SPEED;
    if (noteY3 > SCREEN_HEIGHT) {
        // 화면 밑으로 나가면 초기 위치로 리셋
        noteY3 = -100;
        printf("miss!\n");
        noteJudge = 1;
    }

}
void moveNote4() {
    noteY4 += NOTE_SPEED;
    if (noteY4 > SCREEN_HEIGHT) {
        // 화면 밑으로 나가면 초기 위치로 리셋
        noteY4 = -100;
        printf("miss!\n");
        noteJudge = 1;
    }
}

/*
void moveNote01() {
    noteY01 += NOTE_SPEED;
    if (noteY01 > SCREEN_HEIGHT) {
        // 화면 밑으로 나가면 초기 위치로 리셋
        noteY01 = -100;
        printf("miss!\n");
        noteJudge = 1;
    }
}
void moveNote02() {
    noteY02 += NOTE_SPEED;
    if (noteY02 > SCREEN_HEIGHT) {
        // 화면 밑으로 나가면 초기 위치로 리셋
        noteY02 = -100;
        printf("miss!\n");
        noteJudge = 1;
    }
}
void moveNote03() {
    noteY03 += NOTE_SPEED;
    if (noteY03 > SCREEN_HEIGHT) {
        // 화면 밑으로 나가면 초기 위치로 리셋
        noteY03 = -100;
        printf("miss!\n");
        noteJudge = 1;
    }
}
void moveNote04() {
    noteY04 += NOTE_SPEED;
    if (noteY04 > SCREEN_HEIGHT) {
        // 화면 밑으로 나가면 초기 위치로 리셋
        noteY04 = -100;
        printf("miss!\n");
        noteJudge = 1;
    }
}
*/

int main(int argc, char* argv[]) {
    if (!initSDL()) {
        return -1;
    }
    if (!LoadMedia()) {
        closeSDL();
        return -1;
    }
    Mix_PlayMusic(music, -1);        

    while (isRunning) {
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            handleKeyPress(event);
        }
        LoadMedia();
        moveNote1();
        drawNote();
        SDL_Delay(10); // 프레임 속도 제한
    }
    closeSDL();
    return 0;
}

