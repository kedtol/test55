#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glut.h>

#include <vector>
#include <sstream>
#include <algorithm>

#include "Vector2D.h"
#include "Triangle2D.h"
#include "Line.h"
#include "InputHandler.h"
#include "mat4.h"
#include "GameObject.h"

class Camera
{
	Vector3D focuspoint;
	Surface surface;
	Transform transform;
	double speed = 30;
	double camx;
	double camy;
	double focaldistance;
	double surfaceWidth, surfaceHeight, viewportScale;
	Vector2D viewport; // renderer resolution wont impact performance (the engine only casts points)
	std::vector<Triangle2D> drawBuffer;
	std::vector<Triangle3D> drawBuffer3D;
	Vector3D gravForce;

	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_shaderProgram;

	SDL_GLContext* gcontext;
	InputHandler* ih;
	Vector2D castTo2D(Vector3D v, bool* failed);
	void updateRotation();
	void movement();
	void buildShader();
public:
	Camera() {}
	Camera(SDL_GLContext* _gcontext,InputHandler* _ih);

	void action();
	void draw();
	//SDL_Renderer* getR() { return renderer; }
	void loadDrawBuffer(Mesh mesh,bool* faces);
	void drawGameObject(GameObject& go);

	Vector3D getPos() const { return focuspoint; }
	~Camera()
	{
		glDeleteProgram(m_shaderProgram);
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragmentShader);
	}
	
};

#endif
