#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL.h>
#include <vector>

#include "Vector3D.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Triangle2D.h"
#include "Line.h"
#include "InputHandler.h"

class Camera
{
	Vector3D focuspoint;
	Surface surface;
	Transform transform;
	double focaldistance = 300;
	double surfaceWidth, surfaceHeight, viewportScale;
	Vector2D viewport; // renderer resolution wont impact performance (the engine only casts points)
	std::vector<Triangle2D> drawBuffer;
	SDL_Renderer* renderer;
	InputHandler* ih;
	Vector2D castTo2D(Vector3D v);
	void updateRotation();
	void movement();

public:
	Camera() {}
	Camera(SDL_Renderer* _renderer,InputHandler* _ih);

	void action();
	void draw();
	
	void loadDrawBuffer(Mesh mesh);
};

#endif
