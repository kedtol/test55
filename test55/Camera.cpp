#include "Camera.h"
#include "Line.h"


Vector2D Camera::castTo2D(Vector3D v)
{
	Line line = Line(v, v - focuspoint);
	Vector3D intersection;
	double x, y;
	try
	{
		intersection = surface.intersect(line);

		x = (intersection.getZ() - surface.getPos().getZ()) / (transform.getRot().getK().getZ());
		y = (intersection.getY() - surface.getPos().getY() - (x*transform.getRot().getK().getY()) ) / (transform.getRot().getJ().getY());

	}
	catch (const char* e)
	{
		throw "cant cast";
	}
		// no clipping?
	//if (x < surfaceWidth * 2 && x > -surfaceWidth * 2 && y < surfaceHeight * 2 && y > -surfaceHeight * 2)
		return (Vector2D(y + surfaceWidth / 2, x + surfaceHeight / 2) + viewport) * viewportScale;
	//else
	//	throw "cant cast";
}

Camera::Camera(SDL_Renderer* _renderer, InputHandler* _ih)
{
	renderer = _renderer;
	surfaceWidth = 1024;
	surfaceHeight = 768;
	focaldistance = 300;
	viewportScale = 1;
	viewport = Vector2D();
	transform = Transform();
	transform.addPitch(0.7);
	transform.addYaw(0.7);
	focuspoint = Vector3D(0, 0, 0);
	surface = Surface(Vector3D(), focuspoint);
	drawBuffer = std::vector<Triangle2D>();
	ih = _ih;
}

void Camera::updateRotation()
{
	transform.updateRotation();
	transform.rotateSurface(surface, focaldistance, focuspoint);
}

void Camera::movement()
{
	if (ih->isButtonHold(6))
	{
		focuspoint += transform.getRot().getJ() * -10;

	}

	if (ih->isButtonHold(7))
	{
		focuspoint += transform.getRot().getJ() * 10;

	}

	if (ih->isButtonHold(8))
	{
		focuspoint += transform.getRot().getI() * 10;
		
	}

	if (ih->isButtonHold(9))
	{
		focuspoint += transform.getRot().getI() * -10;
		
	}

	if (ih->isButtonHold(0))
	{
		transform.addYaw(-0.04);
	}

	if (ih->isButtonHold(1))
	{
		transform.addYaw(0.04);
		
	}

	if (ih->isButtonHold(2))
	{
		transform.addPitch(-0.04);
		
	}

	if (ih->isButtonHold(3))
	{
		transform.addPitch(+0.04);
		
	}

	if (ih->isButtonHold(10))
	{

		focuspoint += transform.getRot().getK() * -10;


	}

	if (ih->isButtonHold(11))
	{

		focuspoint += transform.getRot().getK() * +10;


	}
}

void Camera::action()
{
	movement();
	updateRotation();
}

void Camera::draw()
{
	for (size_t i = 0; i < drawBuffer.size(); i++)
	{
		drawBuffer[i].draw(renderer);
	}
	drawBuffer.clear();
}

void Camera::loadDrawBuffer(Mesh mesh)
{
	if (mesh.getTriMode()) // load, cast, put into rendererBuffer
	{
		for (size_t i = 0; i < mesh.getIndexBufferSize()-2; i+=3)
		{
			int iterator = static_cast<int>(i);
			int sol = iterator / 3;
			size_t vo = 0;
			if (sol < mesh.getTriCount())
				vo = sol; //size_t scam
			int index = mesh.shareIndex()[i];
			Triangle3D tri = Triangle3D(mesh.loadVertex(mesh.shareIndex()[i]-1), mesh.loadVertex(mesh.shareIndex()[i+1] - 1), mesh.loadVertex(mesh.shareIndex()[i+2] - 1),mesh.loadBakedMaterial(vo));
			// todo: culling
			try
			{
				drawBuffer.push_back(Triangle2D(castTo2D(tri.getV1()), castTo2D(tri.getV2()), castTo2D(tri.getV3()), tri.getM(), tri.getDistance(focuspoint)));
			}
			catch (const char* e)
			{
				//printf("he");
			}
			
		}
	}
	else // khm todo: abstract class for point groups -> then line strip
	{

	}
}