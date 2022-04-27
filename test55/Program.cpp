#include "Program.h"

Program::Program(SDL_Renderer* _renderer,InputHandler* _ih)
{
	//rl.loadMeshes();
	camera = Camera(_renderer,_ih);
	ih = _ih;
	//map.push_back(GameObject(Transform(Vector3D()), rand() % 400 + 100));
	for (int i = 0; i < 100; i++)
	{
	//	map.push_back(GameObject(Transform(Vector3D(rand()%10000, rand() % 10000, rand() % 10000-4000)),rand()%200+100));
	}
	map.push_back(GameObject(Transform(Vector3D(0,0,0)),300,20,20));
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
