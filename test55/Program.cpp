#include "Program.h"

Program::Program(SDL_GLContext* _gcontext,InputHandler* _ih)
{
	//rl.loadMeshes();
	camera = Camera(_gcontext,_ih);
	ih = _ih;
	//map.push_back(GameObject(Transform(Vector3D()), rand() % 400 + 100));
	for (int i = 0; i < 10; i++)
	{
		map.push_back(GameObject(Transform(Vector3D(rand()%10000, rand() % 10000, rand() % 10000-4000)),rand()%200+100));
	}
	map.push_back(GameObject(Transform(Vector3D(0,0,0)),2000,40,40));
	map.push_back(GameObject(Transform(Vector3D(0, 0, 0))));
}

void Program::actionLoop()
{
	for (size_t i = 0; i < map.size(); i++)
	{
		map[i].action();
	}

	if (ih->isButtonPressed(10))
		mode++;
	if (ih->isButtonPressed(11) && mode > 0)
		mode--;

	Vector2D v;
	
	if (mode == 0)
		v = v1;
	if (mode == 1)
		v = v2;
	if (mode == 2)
		v = v3;
	
	if (ih->isButtonHold(0))
		v+=Vector2D(-10,0);
	if (ih->isButtonHold(1))
		v+=Vector2D(10,0);

	if (ih->isButtonHold(2))
		v += Vector2D(0, -10);
	if (ih->isButtonHold(3))
		v += Vector2D(0, 10);

	if (mode == 0)
		v1 = v;
	if (mode == 1)
		v2 = v;
	if (mode == 2)
		v3 = v;


	camera.action();
}

void Program::drawCycle()
{
	for (size_t i = 0; i < map.size(); i++)
	{
		map[i].draw(&camera);
	}

	
	camera.draw();
	//Triangle2D t =Triangle2D(v1, v2, v3, Material(255, 0, 0), 0);
	

	//Sint16 vx[4] ={100,200,200,100};
	//Sint16 vy[4] = {100,100,200,200};
	//filledPolygonRGBA(camera.getR(), vx, vy, 5,200, 200, 200, 255);
	//t.draw(camera.getR());
}
