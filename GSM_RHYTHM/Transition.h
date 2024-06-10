#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>


void Transition(SDL_Renderer* rend, SDL_Texture* tex) {
	for (int i = 0; i <= 255; i++)
	{
		SDL_SetTextureAlphaMod(tex, i);
		SDL_RenderCopy(rend, tex, NULL, NULL);
		SDL_RenderPresent(rend);
	}
}