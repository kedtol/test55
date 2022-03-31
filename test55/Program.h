#pragma once
#include <SDL.h>

#include "Camera.h"
#include "GameObject.h"
#include "InputHandler.h"

class Program
{
	Camera camera;
	std::vector<GameObject> map;
	InputHandler* ih;

public:
	Program(SDL_Renderer* _renderer, InputHandler* _ih);
	void actionLoop();
	void drawCycle();
};