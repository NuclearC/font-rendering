#include "Font.h"

#include <algorithm>

namespace NC {
	namespace Font {
		FT_Library Font::library = {};

		Font::Font(const std::string& filename, int size, int outline)
		{
			int res = FT_New_Face(library, filename.c_str(), 0, &face);
			if (res != 0) {

			}
			FT_Set_Pixel_Sizes(face, 0, size);
			FT_Stroker_New(library, &stroker);
			FT_Stroker_Set(stroker, outline * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
		}


		Font::~Font()
		{
			FT_Stroker_Done(stroker);
			FT_Done_Face(face);
		}

		void Font::MeasureText(const std::string& text, int& width, int& height) const
		{
			width = 0;
			height = 0;
			// measure the text in the first place
			for (auto ch : text) {
				int index = FT_Get_Char_Index(face, ch);
				FT_Load_Glyph(face, index, 0);

				FT_GlyphSlot slot = face->glyph;

				width += slot->bitmap_left + slot->advance.x >> 6;
				height = std::max(height, int(slot->bitmap_top + slot->bitmap.rows));
			}
		}

		Character Font::Render(char ch) const
		{
			int index = FT_Get_Char_Index(face, ch);
			FT_Load_Glyph(face, index, 0);
			FT_GlyphSlot slot = face->glyph;
			FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
			FT_Bitmap bmp = slot->bitmap;

			CharacterMetrics metrics;
			metrics.x = slot->bitmap_left;
			metrics.y = slot->bitmap_top;
			metrics.horizontalAdvance = slot->advance.x >> 6;
			
			Bitmap bitmap(bmp.width, bmp.rows);
			std::memcpy(bitmap.GetRawData(), bmp.buffer, bmp.pitch * bmp.rows);

			return Character(ch, std::move(bitmap), metrics);
		}

		Character Font::RenderStroke(char ch) const
		{
			int index = FT_Get_Char_Index(face, ch);
			FT_Load_Glyph(face, index, 0);

			FT_Glyph glyph;
			FT_Get_Glyph(face->glyph, &glyph);
			FT_Glyph_StrokeBorder(&glyph, stroker, false, true);
			FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, nullptr, true);

			FT_BitmapGlyph bmpGlyph = (FT_BitmapGlyph)glyph;
			FT_Bitmap bmp = bmpGlyph->bitmap;

			CharacterMetrics metrics;
			metrics.x = bmpGlyph->left;
			metrics.y = bmpGlyph->top;
			metrics.horizontalAdvance = face->glyph->advance.x >> 6;

			Bitmap bitmap(bmp.width, bmp.rows);
			std::memcpy(bitmap.GetRawData(), bmp.buffer, bmp.pitch * bmp.rows);

			return Character(ch, std::move(bitmap), metrics);
		}

		Bitmap Font::Render(const std::string& text) const
		{
			int offsetX = 0;
			for (auto ch : text) {
				int index = FT_Get_Char_Index(face, ch);
				FT_Load_Glyph(face, index, 0);
				FT_GlyphSlot slot = face->glyph;
				FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

				offsetX += slot->bitmap_left + slot->advance.x >> 6;
			}

			return {};
		}

	}
}
