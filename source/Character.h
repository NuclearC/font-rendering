
#ifndef NC_FONTLIB_CHARACTER_H_
#define NC_FONTLIB_CHARACTER_H_

#include "Bitmap.h"

namespace NC {
	namespace Font {

		using CharacterType = char;

		struct CharacterMetrics {
			int x, y; // coordinates for the character (y is from the bottom)
			int horizontalAdvance; // the number of pixels to advance in the X direction for the next character
		};

		class Character {
		private:
			Bitmap bitmap;
			CharacterMetrics metrics;
			CharacterType ch;

		public:
			Character(CharacterType ch, const Bitmap& bitmap,
				const CharacterMetrics& metrics);
			~Character();

			const Bitmap& GetBitmap() const;
			const CharacterMetrics& GetMetrics() const;
			char GetCharacter() const;

		};

	}
}

#endif // NC_FONTLIB_CHARACTER_H_
