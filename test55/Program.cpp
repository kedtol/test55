#include "Program.h"

Program::Program(SDL_Renderer* _renderer,InputHandler* _ih)
{
	camera = Camera(_renderer,_ih);
	ih = _ih;
	map.push_back(GameObject(Transform(Vector3D(900,0,0))));
	int a = 1;
}

void Program::actionLoop()
{
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
