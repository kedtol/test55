#include "Program.h"

Program::Program(SDL_Renderer* _renderer,InputHandler* _ih)
{
	camera = Camera(_renderer,_ih);
	ih = _ih;
	//map.push_back(GameObject(Transform(Vector3D()), rand() % 400 + 100));
	for (int i = 0; i < 100; i++)
	{
		map.push_back(GameObject(Transform(Vector3D(rand()%8000, rand() % 8000, rand() % 8000)),rand()%400+100));
	}
}

void Program::actionLoop()
{
	for (size_t i = 0; i < map.size(); i++)
	{
		map[i].action();
	}
	camera.action();
}

void Program::drawCycle()
{
	for (size_t i = 0; i < map.size(); i++)
	{
		map[i].draw(&camera);
	}

	camera.draw();
}
