#include <stdio.h>
#include <SDL.h>
#include <Windows.h>
#include <stdbool.h>

extern int SoundSetting;
extern bool isTutorialoff;
extern int CoinNum;
extern int NewRecord;
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
    int Admin;
    Sound = SoundSetting;
    int CoinAnswer = CoinNum;
    int RecordNew = NewRecord;
    printf("\n�����ϰ� ���� ���� �����ϼ���.\n");
    printf("1. ���� ����\n");
    printf("2. Ʃ�丮�� ����\n\n");
    printf("����Ϸ��� 0�� �Է��ϼ���.\n\n");
    printf("���� �߰� ����\n");
    scanf_s("%d", &num);
    if (num == 1225) {
        Admin = 0;
        system("cls");
        FILE* fip = NULL;
        fip = fopen("data.txt", "w+");
        if (fip == NULL) {
            printf("���Ͽ��� ����\n");
        }
        while (true)
        {
            system("cls");
            printf("������ ���\n\n");
            printf("������ ����� �����ϼ���\n");
            printf("1. �ְ� ���� �ʱ�ȭ\n");
            printf("2. ���� �ʱ�ȭ\n");
            scanf_s("%d", &Admin);
            if (Admin == 1) {
                fprintf(fip, "%d\n%d", 0, CoinAnswer);
                fclose(fip);
                system("cls");
                return 0;
            }
            else if (Admin == 2) {
                fprintf(fip, "%d\n%d", RecordNew, 0);
                fclose(fip);
                system("cls");
                return 0;
            }
            else {
                printf("�߸��� �Է��Դϴ�!\n");
                Sleep(500);
                continue;
            }
        }
    }
    if (num == 0) {
        system("cls");
        return 0;
    }
    if (num > 2) {
        printf("������ �߸��Ǿ����ϴ�!");
        Sleep(1000);
        system("cls");
    }
    else if (num == 1) {
        while (true)
        {
            system("cls");
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
    else if (num == 2) {
        int x;
        x = TutorialSetting();
        if (x == 1) {
            isTutorialoff = true;
            printf("������ �Ϸ�Ǿ����ϴ�!\n");
            return Sound;
        }
        else {
            isTutorialoff = false;
            printf("������ �Ϸ�Ǿ����ϴ�!\n");
            return Sound;
        }
    }
}

int TutorialSetting() {
    system("cls");
    char check = 0;
    while (true)
    {
        printf("Ʃ�丮���� ���ðڽ��ϱ�?(�� ������ Ȱ��ȭ ��, ������ Ʃ�丮���� ������ �ʽ��ϴ�!)\n");
        printf("����� �� ������ ������ Ű�� �� �� �ֽ��ϴ�!\n");
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
            printf("�Է� ���� �߸��Ǿ����ϴ�!\n");
            Sleep(500);
            system("cls");
            continue;
        }
    }

}