#include "Camera.h"


bool compare(Triangle2D t1, Triangle2D t2)
{
	if (t1.getD() > t2.getD())
		return true;
	else
		return false;
}

Vector2D Camera::castTo2D(Vector3D v, bool* failed)
{
	Line line = Line(v, v - focuspoint);
	Vector3D intersection;
	double x, y;

	intersection = surface.intersect(line,failed);
	
	if (!(*failed))
	{
		x = (intersection.getZ() - surface.getPos().getZ()) / (transform.getRot().getK().getZ());
		y = (intersection.getY() - surface.getPos().getY() - (x*transform.getRot().getK().getY()) ) / (transform.getRot().getJ().getY());
		
		if (x < surfaceWidth * 2 && x > -surfaceWidth * 2 && y < surfaceHeight * 2 && y > -surfaceHeight * 2)
			return (Vector2D(y + surfaceWidth / 2, x + surfaceHeight / 2) + viewport) * viewportScale;
		else
			*failed = true;
	}

	// no clipping?
	
	return Vector2D();
}

Camera::Camera(SDL_GLContext* _gcontext, InputHandler* _ih)
{
	gcontext = _gcontext;
	surfaceWidth = 512;
	surfaceHeight = 384;
	focaldistance = 300;
	viewportScale = 1;
	viewport = Vector2D();
	transform = Transform();
	transform.addPitch(3.14);
	transform.addYaw(3.14);
	focuspoint = Vector3D(0, 0, 0);
	surface = Surface(Vector3D(), focuspoint);
	drawBuffer = std::vector<Triangle2D>();
	ih = _ih;
	gravForce = Vector3D(0, 0, 10);
	buildShader();
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
		double z = focuspoint.getZ();
		focuspoint += transform.getRot().getJ() * -speed;
		focuspoint.setZ(z);
	}

	if (ih->isButtonHold(7))
	{
		double z = focuspoint.getZ();
		focuspoint += transform.getRot().getJ() * speed;
		focuspoint.setZ(z);
	}

	if (ih->isButtonHold(8))
	{
		double z = focuspoint.getZ();
		focuspoint += transform.getRot().getI() * speed;
		focuspoint.setZ(z);
	}

	if (ih->isButtonHold(9))
	{
		double z = focuspoint.getZ();
		focuspoint += transform.getRot().getI() * -speed;
		focuspoint.setZ(z);
	}

	if (ih->isButtonHold(10))
	{
		focuspoint += Vector3D(0,0, -speed);
	}

	if (ih->isButtonHold(11))
	{
		focuspoint += Vector3D(0, 0, speed);
	}

	if (ih->isButtonHold(0))
	{
		transform.addYaw(0.03);
	}

	if (ih->isButtonHold(1))
	{
		transform.addYaw(-0.03);
	}

	if (ih->isButtonHold(2))
	{
		transform.addPitch(0.03);
	}

	if (ih->isButtonHold(3))
	{
		transform.addPitch(-0.03);
	}

	if (ih->getMouse_x() < -10)
	{
		transform.addYaw(0.06);
		SDL_WarpMouseInWindow(NULL, 512, 384);
	}

	if (ih->getMouse_x() > 10)
	{
		transform.addYaw(-0.06);
		SDL_WarpMouseInWindow(NULL, 512, 384);
	}
	
	if (ih->getMouse_y() < -10)
	{
		transform.addPitch(0.06);
		SDL_WarpMouseInWindow(NULL, 512, 384);
	}

	if (ih->getMouse_y() > 10)
	{
		transform.addPitch(-0.06);
		SDL_WarpMouseInWindow(NULL, 512, 384);
	}
	
}

void Camera::action()
{
	movement();
	updateRotation();
}

void Camera::buildShader()
{
	const GLchar* vertexSource =
		"#version 330 core\n"
		"in vec2 position;"
		"in vec3 color;"
		"out vec3 Color;"
		"void main()"
		"{"
		"    gl_Position = vec4(position, 0.0, 1.0);"
		"    Color = color;"
		"}";
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShader, 1, &vertexSource, NULL);
	glCompileShader(m_vertexShader);

	const GLchar* fragmentSource =
		"#version 330 core\n"
		"in vec3 Color;"
		"out vec4 outColor;"
		"void main()"
		"{"
		"    outColor = vec4(Color, 1.0f);"
		"}";
	/*"#version 330 core\n"
	"uniform float maxIterations;"
	"in vec2 fragCoord;"
	"out vec4 outColor;"
	"void main()"
	"{"
	"    outColor = vec4(iterateMandelbrot(fragCoord),0f,0f,1.0f);"
	"}"
	"vec2 squareImaginary(vec2 number) {"
	"return vec2("
	"	pow(number.x, 2) - pow(number.y, 2),"
	"	2 * number.x * number.y"
	");"
	"}"
	"float iterateMandelbrot(vec2 coord) {"
	"vec2 z = vec2(0, 0);"
	"for (int i = 0;i < maxIterations;i++) {"
	"	z = squareImaginary(z) + coord;"
	"	if (length(z) > 2) return i / maxIterations;"
	"}"
	"return maxIterations;"
	"}";*/

	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(m_fragmentShader);

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);
	glBindFragDataLocation(m_shaderProgram, 0, "outColor");
	glLinkProgram(m_shaderProgram);

	GLint myUniformLocation = glGetUniformLocation(m_shaderProgram, "maxIterations");
	glUniform1f(myUniformLocation, 10);

	GLint posAttrib = glGetAttribLocation(m_shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	GLint colAttrib = glGetAttribLocation(m_shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}

void Camera::draw()
{
	//SDL_RenderSetScale(renderer, 2, 2);
	std::sort(drawBuffer.begin(), drawBuffer.end(), compare);
	glUseProgram(m_shaderProgram);
	//std::cout << drawBuffer.size() << std::endl;

	for (size_t i = 0; i < drawBuffer.size(); i++)
	{
		drawBuffer[i].render(gcontext);
	}
	glUseProgram(0);
	std::stringstream strs;
	strs << drawBuffer.size();
	std::string temp_str = strs.str();
	const char* char_type = (char*)temp_str.c_str();
	//stringRGBA(renderer, 10, 10, char_type, 255, 255, 255, 255);
	drawBuffer.clear();
	drawBuffer.shrink_to_fit();
}

void Camera::loadDrawBuffer(Mesh mesh, bool* faces)
{
	if (mesh.getTriMode()) // load, cast, put into rendererBuffer
	{
		for (size_t i = 0; i < mesh.getIndexBufferSize()-2; i+=3)
		{
			// -READING-
				int iterator = static_cast<int>(i);
				int sol = iterator / 3;
				size_t vo = 0; // every third vertex
				if (sol < mesh.getTriCount())
					vo = sol; //size_t scam 
			
				int normalIndex = mesh.shareNormalIndex()[vo]; // get the normal buffer index

				Triangle3D tri = Triangle3D(mesh.loadVertex(mesh.shareIndex()[i]-1), mesh.loadVertex(mesh.shareIndex()[i+1] - 1), mesh.loadVertex(mesh.shareIndex()[i+2] - 1), Material());
			//--

			// -CULLING-
				Vector3D normal = mesh.loadNormal(normalIndex-1); // normalbuffer stores normal vectors/face
				if (normal.dot(focuspoint - tri.getWpoint()) < 0)
					continue;

				// -AGRESSIVE Z CULLING
				if (abs(tri.getWpoint().getZ() - focuspoint.getZ()) > 60000)
					continue;
				// --

				// -VOXEL CULLING-
					if (faces != NULL)
					{
						if (!faces[3] && (i == 0 || i == 3))  // ytop
							continue;
						if (!faces[5] && (i == 6 || i == 9))  // xtop
							continue;
						if (!faces[4] && (i == 12 || i == 15))  // xbottom
							continue;
						if (!faces[2] && (i == 18 || i == 21))  // ybottom
							continue;
						if (!faces[1] && (i == 24 || i == 27))  // ztop
							continue;
						if (!faces[0] && (i == 30 || i == 33))  // zbottom
							continue;
					}
				// --
			//--

			// -CASTING-
				bool failed = false;

				// cast vertices
				Vector2D v1 = castTo2D(tri.getV1(), &failed);
				Vector2D v2 = castTo2D(tri.getV2(), &failed);
				Vector2D v3 = castTo2D(tri.getV3(), &failed);

				// load materials
				Material m1 = mesh.loadBakedMaterial(mesh.shareIndex()[i] - 1);
				Material m2 = mesh.loadBakedMaterial(mesh.shareIndex()[i+1] - 1);
				Material m3 = mesh.loadBakedMaterial(mesh.shareIndex()[i+2] - 1);

				// compose 2d triangle
				Triangle2D t = Triangle2D(v1, v2,v3, m1,m2,m3, tri.getDistance(focuspoint));
			//--

			// -PUSHBACK-
				if (!failed)
					drawBuffer.push_back(t);
			//--
		}
	}
	else // khm todo: abstract class for point groups -> then line strip
	{

	}
}
