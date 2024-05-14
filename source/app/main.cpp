#include "Font.h"

#include "freetype/freetype.h"
#include "SDL3/SDL.h"

static SDL_Window* window;
static SDL_Renderer* renderer;

int main() {
	using namespace NC::Font;

	FT_Init_FreeType(&Font::library);

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("test", 640, 480, {});
	renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_PRESENTVSYNC);

	SDL_Color colors[256];
	for (int i = 0; i < 256; i++)
	{
		colors[i] = SDL_Color{ 255, 255, 255 };
		colors[i].a = i;
	}

	SDL_Texture* texture;

	SDL_Surface* surface;

	SDL_RenderClear(renderer);
	{
		Font f = Font("./fonts/Bitter/static/Bitter-Bold.ttf", 100, 3);
		int width = 0, height = 0;
		f.MeasureText("Hello World", width, height);
		surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
		int offsetX = 0;

		for (auto chh : "Hello World") {
			Character ch = f.RenderStroke(chh);
			const Bitmap& b = ch.GetBitmap();

			SDL_Surface * chSurface = SDL_CreateSurfaceFrom(b.GetRawData(), b.GetWidth(), b.GetHeight(), b.GetWidth(),
				SDL_PixelFormatEnum::SDL_PIXELFORMAT_INDEX8);
			chSurface->format->palette->colors = colors;

			SDL_Rect dest{
				offsetX, 100 - ch.GetMetrics().y,
				b.GetWidth(), b.GetHeight()
			};
			SDL_BlitSurface(chSurface, nullptr, surface, &dest);

			offsetX += ch.GetMetrics().horizontalAdvance;

			chSurface->format->palette->colors = nullptr;
			SDL_DestroySurface(chSurface);
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

		SDL_FRect target_rect = { 0, 0, width, height };
		SDL_RenderTexture(renderer, texture, nullptr, &target_rect);
	}


	SDL_RenderPresent(renderer);

	SDL_Delay(10000);

	SDL_Quit();

	FT_Done_FreeType(Font::library);

	return 0;
}
