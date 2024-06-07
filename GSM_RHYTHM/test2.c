#include <SDL.h>

typedef struct AppData {
	SDL_Window* window;
	SDL_Surface* window_Surface;
	SDL_Surface* player_Surface;
} AppData;

int main(int argc, char* argv[]) {
	AppData ad;
	int SDL_BlitSurface(SDL_Surface * src, const SDL_Rect * srcrect, SDL_Surface * dst, SDL_Rect * dstrect);
	ad.player_Surface = SDL_LoadBMP("Image/player-Sheet.bmp");
	SDL_SetColorKey(ad.player_Surface, SDL_TRUE, SDL_MapRGB(ad.player_Surface->format, 100, 100, 255));
	ad.window_Surface = SDL_GetWindowSurface(ad.window);
	SDL_BlitSurface(ad.player_Surface, NULL, ad.window_Surface, NULL);
}