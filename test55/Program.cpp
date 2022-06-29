#include "Program.h"

Program::Program(SDL_GLContext* _gcontext,InputHandler* _ih)
{
	rl.loadMeshes();
	camera = Camera(_gcontext,_ih);
	ih = _ih;
	//map.push_back(GameObject(Transform(Vector3D()), rand() % 400 + 100));
	for (int i = 0; i < 10; i++)
	{
		map.push_back(GameObject(Transform(Vector3D(rand()%10000, rand() % 10000, rand() % 10000-4000)), rand() % 200 + 100));
	}
	
	//map.push_back(GameObject(Transform(Vector3D(0,0,0)),2100,320,320));
	map.push_back(GameObject(Transform(Vector3D(5000, 1000,2000)),rl.getMesh(0)));
	map.push_back(GameObject(Transform(Vector3D(5000, 1000, 2000)), rl.getMesh(1)));
	map.push_back(GameObject(Transform(Vector3D(5000, 1000, 2000)), rl.getMesh(2)));
	map.push_back(GameObject(Transform(Vector3D(5000, 1000, 2000)), rl.getMesh(3)));
	map.push_back(GameObject(Transform(Vector3D(5000, 1000, 2000)), rl.getMesh(4)));
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
