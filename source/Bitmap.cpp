#include "Bitmap.h"

#include <cstring>
#include <iostream>

namespace NC {
	namespace Font {
		Bitmap::Bitmap() : width(0), height(0), data(nullptr)
		{
		}

		Bitmap::Bitmap(int width, int height) : data(new char[width* height])
		{
			this->width = width;
			this->height = height;
		}

		Bitmap::Bitmap(const Bitmap& other) : width(other.width), 
			height(other.height), data(new char[other.width* other.height])
		{
			std::memcpy(data, other.data, other.width * other.height);
		}

		Bitmap::Bitmap(Bitmap&& other) : width(other.width),
			height(other.height), data(other.data)
		{
			other.data = nullptr;
		}

		Bitmap::~Bitmap()
		{
			if (data != nullptr)
				delete[] data;
		}

		char* Bitmap::GetRawData() const
		{
			return data;
		}

		int Bitmap::GetWidth() const
		{
			return width;
		}

		int Bitmap::GetHeight() const
		{
			return height;
		}
	}
}
