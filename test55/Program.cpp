#include "Program.h"

Program::Program(SDL_GLContext* _gcontext,InputHandler* _ih)
{
	rl.loadMeshes();
	camera = Camera(_gcontext,_ih);
	ih = _ih;
	lights.push_back(Light(Vector3D(0, 0, -5000), Color(80, 80, 80), 50000, 1));

	//lights.push_back(Light(Vector3D(0,0,-1000),Color(100,100,100),80000,0.4));
	//lights.push_back(Light(Vector3D(40000, 40000, -5000), Color(0, 0, 255), 13000, 0.3));
	//lights.push_back(Light(Vector3D(10000, 10000, -0), Color(255, 0, 0), 20000, 0.3));
	//lights.push_back(Light(Vector3D(10000, 15000, -0), Color(0, 255, 0), 20000, 0.3));
	//map.push_back(GameObject(Transform(Vector3D(40000, 40000, -2000)), 1000));
	//lights.push_back(Light(Vector3D(300, 1000, 0), Color(255, 255, 255), 5000, 0.4));
	//lights.push_back(Light(Vector3D(0, 0, 1000), Color(255, 0, 0), 4000, 1));
	//map.push_back(GameObject(Transform(Vector3D()), rand() % 400 + 100));

	
	//map.push_back(GameObject(Transform(Vector3D(0, 0, 0)), 1000));
	//map.push_back(GameObject(Transform(Vector3D(0, 3000, 500)), 1000));
	//map.push_back(GameObject(Transform(Vector3D(5000, 0, 1600)), 1000));

	for (int i = 0; i < 50; i++)
	{
		map.push_back(GameObject(Transform(Vector3D(rand()%100000000, rand() % 100000000, rand() % 100000-4000)), rand() % 200 + 1000));
		//map.push_back(GameObject(Transform(Vector3D(rand() % 10000, rand() % 10000, rand() % 20000)), rl.getMesh(0)));
	}
	//map.push_back(GameObject(Transform(Vector3D(rand() % 10000, rand() % 10000, rand() % 20000)), rl.getMesh(0)));
	//map.push_back(GameObject(Transform(Vector3D(0,0,450)),710,100,100));
	
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
		map[i].getMeshp()->resetBakedMaterial();
		for (size_t j = 0; j < lights.size(); j++)
		{
			map[i].getMeshp()->bakeLightSource(lights[j], map[i].getTransform().applyTransform(map[i].getMesh()));
		}
	}
}
