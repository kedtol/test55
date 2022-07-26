#include "Color.h"

void Color::operator+=(Color c)
{
	if (r + c.getR() < 0)
		r = 0;
	else
		if (r + c.getR() > 255)
			r = 255;
		else
			r += c.getR();

	if (g + c.getG() < 0)
		g = 0;
	else
		if (g + c.getG() > 255)
			g = 255;
		else
			g += c.getG();

	if (b + c.getB() < 0)
		b = 0;
	else
		if (b + c.getB() > 255)
			b = 255;
		else
			b += c.getB();
}

Color operator*(Color c,double d)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	if (c.getR() * d > 255)
		r = 255;
	else
		r = c.getR() * d;

	if (c.getG() * d > 255)
		g = 255;
	else
		g = c.getG() * d;

	if (c.getB() * d > 255)
		b = 255;
	else
		b = c.getB() * d;

	return Color(r, g, b);
}

Color operator-(Color c1, Color c2)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	if (c1.getR() - c2.getR() < 0)
		r = 0;
	else
		if (c1.getR() - c2.getR() > 255)
			r = 255;
		else
			r = c1.getR() - c2.getR();

	if (c1.getG() - c2.getG() < 0)
		g = 0;
	else
		if (c1.getG() - c2.getG() > 255)
			g = 255;
		else
			g = c1.getG() - c2.getG();

	if (c1.getB() - c2.getB() < 0)
		b = 0;
	else
		if (c1.getB() - c2.getB() > 255)
			b = 255;
		else
			b = c1.getB() - c2.getB();

	return Color(r,g,b);
}

