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
    printf("\n�����ϰ� ���� ���� �����ϼ���.\n");
    printf("1. ����\n\n");
    printf("����Ϸ��� 0�� �Է��ϼ���.\n\n");
    printf("���� �߰� ����\n");
    scanf_s("%d", &num);
    if (num == 0) {
        system("cls");
        return 0;
    }
    if (num > 1) {
        printf("������ �߸��Ǿ����ϴ�!");
        Sleep(1000);
        system("cls");
    }
    else if (num == 1) {
        while (true)
        {
            printf("���� ����\n");
            printf("���� ���� �� : %d\n", Sound);
            printf("0 ~ 100 ������ ���� �Է��ϼ��� : ");
            scanf_s("%d", &Sound);
            if (Sound > 100 || Sound < 0) {
                printf("������ �߸��Ǿ����ϴ�!");
                Sleep(1000);
                system("cls");
                continue;
            }
            else {
                printf("������ �Ϸ�Ǿ����ϴ�!\n");
                Sleep(500);
                SoundSetting = Sound;
                system("cls");
                return Sound;
            }
        }
    }
}