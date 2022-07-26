#include "Program.h"

Program::Program(SDL_GLContext* _gcontext,InputHandler* _ih)
{
	rl.loadMeshes();
	camera = Camera(_gcontext,_ih);
	ih = _ih;
	lights.push_back(Light(Vector3D(0,0,-1000),Color(100,100,100),10000,10));
	lights.push_back(Light(Vector3D(0, 20, 300), Color(255, 10, 255), 4000, 300));
	lights.push_back(Light(Vector3D(300, 1000, 0), Color(255, 255, 255), 5000, 100));
	lights.push_back(Light(Vector3D(0, 0, 1000), Color(255, 0, 0), 4000, 100));
	//map.push_back(GameObject(Transform(Vector3D()), rand() % 400 + 100));
	for (int i = 0; i < 4; i++)
	{
		map.push_back(GameObject(Transform(Vector3D(rand()%100000, rand() % 100000, rand() % 10000-4000)), rand() % 200 + 1000));
		//map.push_back(GameObject(Transform(Vector3D(rand() % 10000, rand() % 10000, rand() % 20000)), rl.getMesh(0)));
	}
	
	map.push_back(GameObject(Transform(Vector3D(0,0,0)),2100,10,10));
	
	//map.push_back(GameObject(Transform(Vector3D(5000, 1000, 2000)), rl.getMesh(1)));
	//map.push_back(GameObject(Transform(Vector3D(5000, 1000, 2000)), rl.getMesh(2)));
	//map.push_back(GameObject(Transform(Vector3D(5000, 1000, 2000)), rl.getMesh(3)));
	//map.push_back(GameObject(Transform(Vector3D(5000, 1000, 2000)), rl.getMesh(4)));
}

void Program::actionLoop()
{
	Vector3D campos = camera.getPos();
	lights[0].setPos(campos);
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

void Program::lightUpdate()
{
	for (size_t i = 0; i < map.size(); i++)
	{
		map[i].getMesh()->resetBakedMaterial();
		for (size_t j = 0; j < lights.size(); j++)
		{
			map[i].getMesh()->bakeLightSource(lights[j]);
		}
	}
}
