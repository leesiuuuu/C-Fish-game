#include <stdio.h>
#include <SDL.h>
#include <Windows.h>
#include <ctype.h>

extern int SoundSetting;

void Setting(SDL_Renderer* rend, SDL_Texture* BG, SDL_Texture* Window, SDL_Texture* Check) {
    SDL_SetTextureAlphaMod(Window, 80);
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, BG, NULL, NULL);
    SDL_RenderCopy(rend, Window, NULL, NULL);
    SDL_RenderCopy(rend, Check, NULL, NULL);
    SDL_RenderPresent(rend);
}
int SoundSettingWindow() {
    int num;
    int Sound;
    Sound = SoundSetting;
    printf("\n설정하고 싶은 것을 선택하세요.\n");
    printf("1. 사운드\n\n");
    printf("취소하려면 0을 입력하세요.\n\n");
    printf("추후 추가 예정\n");
    scanf_s("%d", &num);
    if (num == 0) {
        system("cls");
        return 0;
    }
    if (num > 1) {
        printf("범위가 잘못되었습니다!");
        Sleep(1000);
        system("cls");
    }
    else if (num == 1) {
        while (true)
        {
            printf("사운드 설정\n");
            printf("현재 사운드 값 : %d\n", Sound);
            printf("0 ~ 100 사이의 값을 입력하세요 : ");
            scanf_s("%d", &Sound);
            if (Sound > 100 || Sound < 0) {
                printf("범위가 잘못되었습니다!");
                Sleep(1000);
                system("cls");
                continue;
            }
            else {
                printf("설정이 완료되었습니다!\n");
                Sleep(500);
                SoundSetting = Sound;
                system("cls");
                return Sound;
            }
        }
    }
}