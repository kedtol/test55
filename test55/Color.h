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
	void invert() 
	{
		
		r = (1 - 256 / (r+1)) * 255;
		g = (1 - 256 / (g+1)) * 255;
		b = (1 - 256 / (b+1)) * 255;
	}

	void operator+=(Color);
};
Color operator*(Color, double);
Color operator-(Color c1, Color c2);