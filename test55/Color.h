#pragma once
class Color 
{
	char r, g, b;

public:
	Color() { r = 0; g = 0; b = 0; }
	Color(char _r, char _g, char _b) { r = _r; g = _g; b = _b; }

	char getR() { return r; }
	char getG() { return g; }
	char getB() { return b; }
};