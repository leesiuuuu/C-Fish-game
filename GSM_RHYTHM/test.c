#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define NOTE_SPEED 5

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool isRunning = true;

// ��Ʈ�� ��ġ
int noteY1 = -100; // ���� ��ġ
int noteY2 = -100; // ���� ��ġ
int noteY3 = -100; // ���� ��ġ
int noteY4 = -100; // ���� ��ġ

bool keyCheck[4] = { false, false, false, false };


void handleKeyPress(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_d:
            printf("1���� ���Ƚ��ϴ�.\n");
            keyCheck[0] = true;
            break;
        case SDLK_f:
            printf("2���� ���Ƚ��ϴ�.\n");
            keyCheck[1] = true;
            break;
        case SDLK_j:
            printf("3���� ���Ƚ��ϴ�.\n");
            keyCheck[2] = true;
            break;
        case SDLK_k:
            printf("4���� ���Ƚ��ϴ�.\n");
            keyCheck[3] = true;
            break;
            // �ʿ��� Ű�� ���� �߰� ó���� ���⿡ �߰��� �� �ֽ��ϴ�.
        default:
            keyCheck[0] = false;
            keyCheck[1] = false;
            keyCheck[2] = false;
            keyCheck[3] = false;
            break;
        }
    }
}

// �Ÿ��� ����ϴ� �Լ�
double calculateDistance(SDL_Rect noteRect, SDL_Rect noteCheck) {
    // ��Ʈ�� �߽� ��ǥ ���
    double noteCenterX = noteRect.x + noteRect.w / 2;
    double noteCenterY = noteRect.y + noteRect.h / 2;

    // ��Ʈ Ȯ�� ������ �߽� ��ǥ ���
    double noteCheckCenterX = noteCheck.x + noteCheck.w / 2;
    double noteCheckCenterY = noteCheck.y + noteCheck.h / 2;

    // �� �� ������ �Ÿ� ���
    double distance = sqrt(pow(noteCenterX - noteCheckCenterX, 2) + pow(noteCenterY - noteCheckCenterY, 2));
    return distance;
}

// �Ÿ��� ���� ������ �����ϴ� �Լ�
void FunctionOnDistance(SDL_Rect noteRect, SDL_Rect noteCheck, int *noteY) {
    // ��Ʈ�� ��Ʈ Ȯ�� ���� ������ �Ÿ� ���
    double distance = calculateDistance(noteRect, noteCheck);

    // �Ÿ��� ���� ���� ����
    if (distance < 40) {
        printf("Perfect\n");
        *noteY = -100;
    }
    else if(distance < 60) {
        printf("great\n");
        *noteY = -100;
    }
    else if (distance < 70) {
        printf("good\n");
        *noteY = -100;
    }
    else if (distance < 0 && distance > -60) {
        printf("great\n");
        *noteY = -100;
    }
    else if (distance > -60 && distance < -70) {
        printf("good\n");
        *noteY = -100;
    }
    else {
        printf("miss!\n");
    }
}

// SDL �ʱ�ȭ �Լ�
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL �ʱ�ȭ ����: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Note Falling", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("������ ���� ����: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("������ ���� ����: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

// SDL ���� �Լ�
void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// ��Ʈ�� �׸��� �Լ�
void drawNote() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // ������ ���
    SDL_RenderClear(renderer);

    // ��Ʈ�� ���������� �׸�
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //��Ʈ ��ġ, ũ�� �ڵ�
    SDL_Rect noteRect1 = {10, noteY1, 60, 20}; 
    SDL_RenderFillRect(renderer, &noteRect1);
    
    SDL_Rect noteRect2 = { 70, noteY2, 60, 20 };
    SDL_RenderFillRect(renderer, &noteRect2);

    SDL_Rect noteRect3 = { 130, noteY3, 60, 20 };
    SDL_RenderFillRect(renderer, &noteRect3);

    SDL_Rect noteRect4 = { 190, noteY4, 60, 20 };
    SDL_RenderFillRect(renderer, &noteRect4);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    //��Ʈ Ȯ�� ����
    SDL_Rect noteCheck1 = { 10, 400, 60, 20 };
    SDL_RenderFillRect(renderer, &noteCheck1);

    SDL_Rect noteCheck2 = { 70, 400, 60, 20 };
    SDL_RenderFillRect(renderer, &noteCheck2);

    SDL_Rect noteCheck3 = { 130, 400, 60, 20 };
    SDL_RenderFillRect(renderer, &noteCheck3);
 
    SDL_Rect noteCheck4 = { 190, 400, 60, 20 };
    SDL_RenderFillRect(renderer, &noteCheck4);
    
    if (keyCheck[0] == true) {
        FunctionOnDistance(noteRect1, noteCheck1, &noteY1);
        keyCheck[0] = false;
    }
    if (keyCheck[1] == true) {
        FunctionOnDistance(noteRect2, noteCheck2, &noteY2);
        keyCheck[1] = false;
    }
    if (keyCheck[2] == true) {
        FunctionOnDistance(noteRect3, noteCheck3, &noteY3);
        keyCheck[2] = false;
    }
    if (keyCheck[3] == true) {
        FunctionOnDistance(noteRect4, noteCheck4, &noteY4);
        keyCheck[3] = false;
    }



    //�� ���� ���� �ڵ�
    SDL_RenderDrawLine(renderer, 10, 2, 10, 500);
    SDL_RenderDrawLine(renderer, 250, 2, 250, 500);
    //�� ���� ���� �ڵ�
    SDL_RenderDrawLine(renderer, 70, 2, 70, 500);
    SDL_RenderDrawLine(renderer, 130, 2, 130, 500);
    SDL_RenderDrawLine(renderer, 190, 2, 190, 500);

    SDL_RenderPresent(renderer);
}

// ��Ʈ �̵� �Լ�
void moveNote1() {
    noteY1 += NOTE_SPEED;
    if (noteY1 > SCREEN_HEIGHT) {
        // ȭ�� ������ ������ �ʱ� ��ġ�� ����
        noteY1 = -100;
        printf("miss!\n");
    }
}
void moveNote2() {
    noteY2 += NOTE_SPEED;

    if (noteY2 > SCREEN_HEIGHT) {
        // ȭ�� ������ ������ �ʱ� ��ġ�� ����
        noteY2 = -100;
        printf("miss!\n");
    }

}
void moveNote3() {
    noteY3 += NOTE_SPEED;
    if (noteY3 > SCREEN_HEIGHT) {
        // ȭ�� ������ ������ �ʱ� ��ġ�� ����
        noteY3 = -100;
        printf("miss!\n");
    }

}
void moveNote4() {
    noteY4 += NOTE_SPEED;
    if (noteY4 > SCREEN_HEIGHT) {
        // ȭ�� ������ ������ �ʱ� ��ġ�� ����
        noteY4 = -100;
        printf("miss!\n");
    }
}


int main(int argc, char* argv[]) {
    if (!initSDL()) {
        return -1;
    }

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            handleKeyPress(event);
        }
        moveNote1();
        moveNote2();
        moveNote3();
        moveNote4();
        drawNote();
        SDL_Delay(10); // ������ �ӵ� ����
    }

    closeSDL();
    return 0;
}
