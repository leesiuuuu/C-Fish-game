#include <stdio.h>
#include <SDL.h>
#include <Windows.h>
#include <stdbool.h>

extern int SoundSetting;
extern bool Tutorial;
int TutorialSetting();

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
    printf("1. 사운드 설정\n");
    printf("2. 튜토리얼 설정\n\n");
    printf("취소하려면 0을 입력하세요.\n\n");
    printf("추후 추가 예정\n");
    scanf_s("%d", &num);
    if (num == 0) {
        system("cls");
        return 0;
    }
    if (num > 2) {
        printf("범위가 잘못되었습니다!");
        Sleep(1000);
        system("cls");
    }
    else if (num == 1) {
        while (true)
        {
            system("cls");
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
    else if (num == 2) {
        int x;
        x = TutorialSetting();
        if (x == 1) {
            Tutorial = true;
            printf("설정이 완료되었습니다!\n");
            return Sound;
        }
        else {
            printf("설정이 완료되었습니다!\n");
            Tutorial = false;
            return Sound;
        }
    }
}

int TutorialSetting() {
    system("cls");
    while (true)
    {
        char check = 0;
        printf("튜토리얼을 끄시겠습니까?(이 설정을 활성화 시, 앞으로 튜토리얼은 나오지 않습니다!)\n");
        printf("당신은 이 설정을 언제든 키고 끌 수 있습니다!\n");
        printf("(y/n) : ");
        scanf_s("%c", &check);
        if (check == 'y' || check == 'Y') {
            return 1;
            break;
        }
        else if (check == 'n' || check == 'N') {
            return 0;
            break;
        }
        else {
            printf("입력 값이 잘못되었습니다!\n");
            Sleep(500);
            system("cls");
            continue;
        }
    }

}