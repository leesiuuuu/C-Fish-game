#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>



void PlayerLogic2(int idx, int state, SDL_Rect* rcspi) {
    idx++;
    rcspi->x = 100 * idx;
    rcspi->y = 100 * state;
    if (idx >= 5)
        idx = 0;
}
