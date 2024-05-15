#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_audio.h>
#include <stdbool.h>



void MapToNote(SDL_Renderer* Rend) {
	SDL_Rect noteReck[3]; //171
	noteReck[0] = (SDL_Rect){10, 665, 60, 20 };
	SDL_RenderFillRect(Rend, &noteReck[0]);
	
	noteReck[1] = (SDL_Rect){ 190, 665, 60, 20 };
	SDL_RenderFillRect(Rend, &noteReck[1]);

	noteReck[2] = (SDL_Rect){ 70, 1002, 60, 20 };
	SDL_RenderFillRect(Rend, &noteReck[2]);
}

/*
void NoteCheckFunction(SDL_Rect noteRec, SDL_Rect noteChec, int y) {
	if (keyCheck[3] == true) {
		FunctionOnDistance(noteRec, noteChec, &y);
		keyCheck[3] = false;
	}
	if (keyCheck[2] == true) {
		FunctionOnDistance(noteRec, noteChec, &y);
		keyCheck[2] = false;
	}
	if (keyCheck[1] == true) {
		FunctionOnDistance(noteRec, noteChec, &y);
		keyCheck[1] = false;
	}
	if (keyCheck[0] == true) {
		FunctionOnDistance(noteRec, noteChec, &y);
		keyCheck[0] = false;
	}
}
*/
