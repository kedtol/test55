#pragma once
#include <SDL.h>

#include "Camera.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "ResourceLoader.h"
#include "Chunk.h"

class Program
{
	Camera camera;
	std::vector<GameObject> map;
	std::vector<Light> lights;
	InputHandler* ih;
	ResourceLoader rl;
	GameObject* solid;
	Chunk* c;
	Chunk* c1;
	Chunk* c2;
public:
	Program(SDL_GLContext* _gcontext, InputHandler* _ih);
	void actionLoop();
	void drawCycle();
	void lightUpdate();
	
};