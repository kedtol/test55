#pragma once
class Color 
{
	unsigned char r, g, b;

public:
	Color() { r = 0; g = 0; b = 0; }
	Color(unsigned char _r, unsigned char _g, unsigned char _b) { r = _r; g = _g; b = _b; }

	unsigned char getR() { return r; }
	unsigned char getG() { return g; }
	unsigned char getB() { return b; }
	void invert() { r = (r - 256) % 256; g = (g - 256) % 256;b = (b - 256) % 256;}

	void operator+=(Color);
};
Color operator*(Color, double);
Color operator-(Color c1, Color c2);