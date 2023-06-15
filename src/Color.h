#pragma once
#include <cstdint>

#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	uint8_t rgba[4];

	inline uint8_t& operator[](const int i)
	{
		return rgba[i];
	}

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
	{
		rgba[0] = r, rgba[1] = g, rgba[2] = b, rgba[3] = a;
	}
	Color(uint8_t Brightness, uint8_t Alpha = 255)
	{
		rgba[0] = rgba[1] = rgba[2] = Brightness, rgba[3] = Alpha;
	}
	Color() {}

	static Color FromHSB(float Hue, float Saturation, float Brightness, int Alpha = 255);
};
#endif