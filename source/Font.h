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
		class Font {
		public:

			static FT_Library library;

		private:

			FT_Face face;
			FT_Stroker stroker;

		public:
			Font(const std::string& filename, int size, int outline);
			~Font();

			void MeasureText(const std::string& text, int& width, int& height) const;

			Character Render(char ch) const;
			Character RenderStroke(char ch) const;

			Bitmap Render(const std::string& text) const;

		};
	}
}

#endif // NC_FONTLIB_FONT_H_
