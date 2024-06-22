#ifndef NC_FONTLIB_FONT_H_
#define NC_FONTLIB_FONT_H_

#include "freetype/freetype.h"
#include "freetype/ftstroke.h"

#include "Bitmap.h"
#include "Character.h"

#include <string>
#include <vector>

namespace NC {
	namespace Font {

		struct RenderedText {
			std::vector<Character> characters;
			int width, height;
		};

		class Font {
		public:

			static FT_Library library;

		private:

			int fontSize;
			int outlineSize;

			FT_Face face;
			FT_Stroker stroker;

		public:
			Font(const std::string& filename, int size, int outline);
			~Font();

			RenderedText Render(const std::string& text) const;
			RenderedText RenderStroke(const std::string& text) const;

			Character Render(char ch) const;
			Character RenderStroke(char ch) const;
		};
	}
}

#endif // NC_FONTLIB_FONT_H_
