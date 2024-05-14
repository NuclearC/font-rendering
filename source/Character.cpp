
#include "Character.h"

namespace NC {
	namespace Font {
		Character::Character(CharacterType ch, const Bitmap& bitmap,
			const CharacterMetrics& metrics) : metrics(metrics), bitmap(bitmap), ch(ch)
		{
			
		}

		Character::~Character()
		{
		}

		const Bitmap& Character::GetBitmap() const
		{
			return bitmap;
		}

		const CharacterMetrics& Character::GetMetrics() const
		{
			return metrics;
		}

		char Character::GetCharacter() const
		{
			return ch;
		}
	}
}