#pragma once
class Material
{
	char r, g, b;
	// i cant really write more... the engine only knows the 3 points of a tri and a color now
public:
	Material(){}
	Material(char r, char g, char b);
	char getR() { return r; }
	char getG() { return g; }
	char getB() { return b; }
};