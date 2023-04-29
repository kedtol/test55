#include "Program.h"


Program::Program(SDL_GLContext* _gcontext,InputHandler* _ih)
{
	rl.loadMeshes();
	camera = Camera(_gcontext,_ih);
	ih = _ih;
	//lights.push_back(Light(Vector3D(40000, 4000, -50000), Color(80, 80, 80), 500000, 1));

	lights.push_back(Light(Vector3D(30000, 30000, -5000), Color(0, 0, 255), 50000, 0.8));
	lights.push_back(Light(Vector3D(30000, -30000, -5000), Color(255, 0, 0), 50000, 0.8));
	lights.push_back(Light(Vector3D(-15000, -15000, -30000), Color(0, 255, 0), 50000, 0.8));

	
	//for (int i = 0; i < 2; i++)
	//{
	//	map.push_back(GameObject(Transform(Vector3D(rand()%100000000, rand() % 100000000, 0)), rand() % 200 + 300));
	//}

	//map.push_back(GameObject(Transform(Vector3D(-0, -0, 0)), 300, 10, 10));

	
	for (int i = 0; i < 1; i++)
	{
		map.push_back(GameObject(Transform(Vector3D(i*100, 0, 0)), rl.getMesh(4)));
		//map.push_back(GameObject(Transform(Vector3D(rand()%1300, rand() % 1300, rand() % 1300)), Mesh(20)));
	}

	
}

void Program::actionLoop()
{
	Vector3D campos = camera.getPos();
	//lights[0].setPos(campos);
	for (size_t i = 0; i < map.size(); i++)
	{
		map[i].action();
	}
	//c->simulate();
	camera.action();
}

void Program::drawCycle()
{
	for (size_t i = 0; i < map.size(); i++)
	{
		camera.drawGameObject(map[i]);
	}
	
	//for (size_t i = 0; i < map.size(); i++)
	//{
	//	map[i].draw(&camera);
	//}

	//camera.draw();
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
