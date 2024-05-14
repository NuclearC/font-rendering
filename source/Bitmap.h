#ifndef NC_FONTLIB_BITMAP_H_
#define NC_FONTLIB_BITMAP_H_

namespace NC {
	namespace Font {
		class Bitmap {
		private:

			char* data;
			int width;
			int height;

		public:
			Bitmap();
			Bitmap(int width, int height);
			Bitmap(const Bitmap& other);
			Bitmap(Bitmap&& other);
			~Bitmap();

			char* GetRawData() const;

			int GetWidth() const;
			int GetHeight() const;
		};
	} 
}



#endif // NC_FONTLIB_BITMAP_H_
