#pragma once
#include <SDL.h>

#include "Camera.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "ResourceLoader.h"

class Program
{
	Camera camera;
	std::vector<GameObject> map;
	InputHandler* ih;
//	ResourceLoader rl;
	Vector2D v1 = Vector2D(400,-100);
	Vector2D v2 = Vector2D(200, 600);
	Vector2D v3 = Vector2D(600, 600);
	size_t mode = 0;
public:
	Program(SDL_GLContext* _gcontext, InputHandler* _ih);
	void actionLoop();
	void drawCycle();
};