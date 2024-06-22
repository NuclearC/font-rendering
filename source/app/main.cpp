

#include "Font.h"

#include "freetype/freetype.h"
#include "SDL3/SDL.h"

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Color colors[256];

SDL_Surface* CreateSurfaceFromText(const NC::Font::RenderedText& text, int baselineY) {
	SDL_Surface* surface = SDL_CreateSurface(text.width, text.height, SDL_PIXELFORMAT_RGBA32);

	int offsetX = 0;
	for (auto& ch : text.characters) {
		const auto& b = ch.GetBitmap();

		SDL_Surface* chSurface = SDL_CreateSurfaceFrom(b.GetRawData(), b.GetWidth(), b.GetHeight(), b.GetWidth(),
			SDL_PixelFormatEnum::SDL_PIXELFORMAT_INDEX8);
		SDL_Palette* palette = SDL_CreatePalette(256);
		SDL_SetPaletteColors(palette, colors, 0, 256);
		SDL_SetSurfacePalette(chSurface, palette);

		SDL_Rect dest{
			offsetX, baselineY - ch.GetMetrics().y,
			b.GetWidth(), b.GetHeight()
		};
		SDL_SetSurfaceBlendMode(chSurface, SDL_BLENDMODE_BLEND);
		SDL_BlitSurface(chSurface, nullptr, surface, &dest);

		offsetX += ch.GetMetrics().horizontalAdvance;

		SDL_DestroyPalette(palette);
		SDL_DestroySurface(chSurface);
	}

	return surface;
}

void PaintText(const NC::Font::Font& font, const std::string& text, int x, int y,
	SDL_Color fontColor, SDL_Color outlineColor) {
	auto normal = font.Render(text);
	auto outlined = font.RenderStroke(text);

	auto normalSurface = CreateSurfaceFromText(normal, 37);
	auto outlinedSurface = CreateSurfaceFromText(outlined, 40);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, outlinedSurface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	SDL_FRect target_rect = { x, y, outlined.width, outlined.height };
	SDL_SetTextureColorMod(texture, outlineColor.r, outlineColor.g, outlineColor.b);
	SDL_RenderTexture(renderer, texture, nullptr, &target_rect);

	SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(renderer, normalSurface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	target_rect = SDL_FRect{ (float)x + 3, (float)y + 3, (float)normal.width, (float)normal.height };
	SDL_SetTextureColorMod(texture, fontColor.r, fontColor.g, fontColor.b);
	SDL_RenderTexture(renderer, texture, nullptr, &target_rect);
	SDL_DestroyTexture(texture);

	SDL_DestroySurface(normalSurface);
	SDL_DestroySurface(outlinedSurface);
}

int main() {
	for (int i = 1; i < 256; i++)
	{
		colors[i] = SDL_Color{ 255, 255, 255, (unsigned char)i };
	}

	using namespace NC::Font;

	FT_Init_FreeType(&Font::library);

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("test", 640, 480, {});
	renderer = SDL_CreateRenderer(window, nullptr);

	SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
	SDL_RenderClear(renderer);
	
	{
		SDL_Texture* texture;
		SDL_Surface* surface;

		Font f = Font("./fonts/Bitter/static/Bitter-Bold.ttf", 50, 3);

		PaintText(f, "Hello world", 100, 100,
			SDL_Color{255,255,255},SDL_Color{0, 0, 0});
	}

	SDL_RenderPresent(renderer);
	bool shouldQuit = false;
	while (!shouldQuit) {
		SDL_Event e{};
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT)
				break;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	FT_Done_FreeType(Font::library);

	return 0;
}
