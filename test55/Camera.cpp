#include "Camera.h"


/*bool compare(Triangle2D t1, Triangle2D t2)
{
	if (t1.getD() > t2.getD())
		return true;
	else
		return false;
}*/

bool compare(Triangle3D t1, Triangle3D t2)
{
	if (t1.getDistance(Vector3D()) > t2.getDistance(Vector3D()))
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
	drawBuffer3D = std::vector<Triangle3D>();
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
	Vector3D front = transform.getRot().getI().normalize();
	Vector3D side = transform.getRot().getJ().normalize();
	Vector3D top = transform.getRot().getK().normalize();
	//glMatrixMode(GL_MODELVIEW_MATRIX);
	if (ih->isButtonHold(6))
	{
		/*double z = focuspoint.getZ();
		focuspoint += transform.getRot().getJ() * speed;
		focuspoint.setZ(z);*/
		focuspoint += side * speed * 0.1;
		//glTranslatef(transform.getRot().getJ().getX()*speed * 0.0001, transform.getRot().getJ().getY()*speed * 0.0001,0);
	}

	if (ih->isButtonHold(7))
	{
		/*double z = focuspoint.getZ();
		focuspoint += transform.getRot().getJ() * -speed;
		focuspoint.setZ(z);*/
		focuspoint += side * -speed * 0.1;
		//glTranslatef(transform.getRot().getJ().getX() * -speed * 0.0001, transform.getRot().getJ().getY() * -speed * 0.0001, 0);
	}

	if (ih->isButtonHold(8))
	{
		/*double z = focuspoint.getZ();
		focuspoint += transform.getRot().getI() * -speed;
		focuspoint.setZ(z);*/
		//focuspoint += Vector3D(-0.1, 0, 0);
		focuspoint += front * speed * 0.1;
		//glTranslatef(transform.getRot().getI().getX() * -speed * 0.0001, transform.getRot().getI().getY() * -speed * 0.0001, 0);
	}

	if (ih->isButtonHold(9))
	{
		/*double z = focuspoint.getZ();
		focuspoint += transform.getRot().getI() * speed;
		focuspoint.setZ(z);*/
		focuspoint += front * -speed * 0.1;
		//glTranslatef(transform.getRot().getI().getX() * speed * 0.0001, transform.getRot().getI().getY() * speed * 0.0001, 0);
	}

	if (ih->isButtonHold(10))
	{
		//focuspoint += Vector3D(0,0, -0.1*speed);
		//glTranslatef(0, 0, speed * 0.0001);
	}

	if (ih->isButtonHold(11))
	{
		//focuspoint += Vector3D(0, 0, 0.1*speed);
		//glTranslatef(0, 0, -speed * 0.0001);
	}
	
	

	if (ih->isButtonHold(0))
	{
		
		transform.addYaw(-0.03);
		//glRotatef(-3, 0.0f, 0.0f, 1.0f);
		//glTranslatef(-focuspoint.getX() * 0.0001, -focuspoint.getY() * 0.0001, -focuspoint.getZ() * 0.0001);
	}

	if (ih->isButtonHold(1))
	{
		transform.addYaw(0.03);
		
		//glRotatef(3, 0.0f, 0.0f, 1.0f);
		//glTranslatef(-focuspoint.getX() * 0.0001, -focuspoint.getY() * 0.0001, -focuspoint.getZ() * 0.0001);
	}

	if (ih->isButtonHold(2))
	{
		transform.addPitch(0.03);
		
		//glRotatef(-3, 1.0f, 0.0, 0.0f);
		//glTranslatef(-focuspoint.getX() * 0.0001, -focuspoint.getY() * 0.0001, -focuspoint.getZ() * 0.0001);
	}

	if (ih->isButtonHold(3))
	{
		transform.addPitch(-0.03);
		//glRotatef(3, 1.0f, 0.0, 0.0f);
		//glTranslatef(-focuspoint.getX() * 0.0001, -focuspoint.getY() * 0.0001, -focuspoint.getZ() * 0.0001);
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
	//transform.setRotCenter(focuspoint);
	
	movement();
	updateRotation();
}

void Camera::buildShader()
{
	glEnable(GL_DEPTH_TEST);
	/*const GLchar* vertexSource =
		"#version 330 core\n"
		"in vec2 position;"
		"in vec3 color;"
		"out vec3 Color;"
		"void main()"
		"{"
		"    gl_Position = vec4(position, 0.0, 1.0);"
		"    Color = color;"
		"}";*/
	const GLchar* vertexSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 vp;"
		"layout(location = 1) in vec3 color;"

		"uniform mat4 MVP;"
		
		"out vec3 Color;"
		
		"void main()"
		"{"
		"    gl_Position = vec4(vp.x,vp.y,vp.z, 1.0f) * MVP;"
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

	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(m_fragmentShader);

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);
	
	glBindFragDataLocation(m_shaderProgram, 0, "outColor");
	glLinkProgram(m_shaderProgram);

	

	/*GLint posAttrib = glGetAttribLocation(m_shaderProgram, "vp");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(GLdouble), 0);

	GLint colAttrib = glGetAttribLocation(m_shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLdouble), (void*)(2 * sizeof(GLfloat)));*/
}

void Camera::draw()
{
	////vertexbuffer
	//glGenBuffers(1, &m_shaderProgram); //create a buffer with "buffer" id
	//glBindBuffer(GL_ARRAY_BUFFER, m_shaderProgram); //bind the buffer (set the "state machine")
	//glBufferData(GL_ARRAY_BUFFER, sizeof(double)*3*3*drawBuffer3D.size(), drawBuffer3D, GL_STATIC_DRAW); //write data to buffer

	////indexbuffer
	//glGenBuffers(1, &m_shaderProgram);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_shaderProgram); //bind the buffer (set the "state machine")
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW); //write data to buffer (gluint is the correct OPENGL size)

	glUseProgram(m_shaderProgram);

	//SDL_RenderSetScale(renderer, 2, 2);
	//std::sort(drawBuffer3D.begin(), drawBuffer3D.end(), compare);
	float MVPtransf[4][4] = { 1, 0, 0, 0,    // MVP matrix, 
							  0, 1, 0, 0,    // row-major!
							  0, 0, 1, 0,
							  0, 0, 0, 1 };

	int location = glGetUniformLocation(m_shaderProgram, "MVP");	// Get the GPU location of uniform variable MVP
	glUniformMatrix4fv(location, 1, GL_TRUE, &MVPtransf[0][0]);	// Load a 4x4 row-major float matrix to the specified location

	int worldpos = glGetUniformLocation(m_shaderProgram, "wp");
	glUniform3f(worldpos, focuspoint.getX(), focuspoint.getY(), focuspoint.getZ()); // 3 floats

	//std::cout << drawBuffer.size() << std::endl;
	
	/*for (size_t i = 0; i < drawBuffer.size(); i++)
	{
		drawBuffer[i].render(gcontext);
	}*/

	glMatrixMode(GL_PROJECTION); // projection matrix for "3d"
	glLoadIdentity();
	gluPerspective(3.1415f/1.2f, (float)1024 / (float)764, 0.01f, 1000.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Vector3D front = transform.getRot().getI().normalize();
	Vector3D up = transform.getRot().getK();
	gluLookAt(focuspoint.getX(), focuspoint.getY(), focuspoint.getZ(),
		front.getX(), front.getY(), front.getZ(),
		up.getX(), up.getY(), up.getZ()); // view matrix (camara rotation)

	for (size_t i = 0; i < drawBuffer3D.size(); i++)
	{
		drawBuffer3D[i].render(gcontext);
	}

	glUseProgram(0);
	//std::stringstream strs;
	//strs << drawBuffer.size();
	//std::string temp_str = strs.str();
	//const char* char_type = (char*)temp_str.c_str();
	//stringRGBA(renderer, 10, 10, char_type, 255, 255, 255, 255);
	drawBuffer3D.clear();
	drawBuffer3D.shrink_to_fit();
	
	//drawBuffer.clear();
	//drawBuffer.shrink_to_fit();
}

void Camera::loadDrawBuffer(Mesh meshy, bool* faces)
{
	//transform.setPos(focuspoint);
	//Mesh mesh = transform.applyTransform(meshy);
	Mesh mesh = meshy;
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

				Triangle3D tri = Triangle3D(
					mesh.loadVertex(mesh.shareIndex()[i]-1), 
					mesh.loadVertex(mesh.shareIndex()[i+1] - 1),
					mesh.loadVertex(mesh.shareIndex()[i+2] - 1),
					mesh.loadBakedMaterial(mesh.shareIndex()[i] - 1),
					mesh.loadBakedMaterial(mesh.shareIndex()[i + 1] - 1),
					mesh.loadBakedMaterial(mesh.shareIndex()[i + 2] - 1));
			//--

			// -CULLING-
				Vector3D normal = mesh.loadNormal(normalIndex-1); // normalbuffer stores normal vectors/face
				//if (normal.dot(focuspoint - tri.getWpoint()) < 0)
				//	continue;

				// -AGRESSIVE Z CULLING
				//if (abs(tri.getWpoint().getZ() - focuspoint.getZ()) > 60000)
					//continue;
				// --

				// -VOXEL CULLING-
					//if (faces != NULL)
					//{
					//	if (!faces[3] && (i == 0 || i == 3))  // ytop
					//		continue;
					//	if (!faces[5] && (i == 6 || i == 9))  // xtop
					//		continue;
					//	if (!faces[4] && (i == 12 || i == 15))  // xbottom
					//		continue;
					//	if (!faces[2] && (i == 18 || i == 21))  // ybottom
					//		continue;
					//	if (!faces[1] && (i == 24 || i == 27))  // ztop
					//		continue;
					//	if (!faces[0] && (i == 30 || i == 33))  // zbottom
					//		continue;
					//}
				// --
			//--

			// -CASTING-
				//bool failed = false;

				//// cast vertices
				//Vector2D v1 = castTo2D(tri.getV1(), &failed);
				//Vector2D v2 = castTo2D(tri.getV2(), &failed);
				//Vector2D v3 = castTo2D(tri.getV3(), &failed);

				//// load materials
				//Material m1 = mesh.loadBakedMaterial(mesh.shareIndex()[i] - 1);
				//Material m2 = mesh.loadBakedMaterial(mesh.shareIndex()[i+1] - 1);
				//Material m3 = mesh.loadBakedMaterial(mesh.shareIndex()[i+2] - 1);

				//// compose 2d triangle
				//Triangle2D t = Triangle2D(v1, v2,v3, m1,m2,m3, tri.getDistance(focuspoint));
			//--

			// -PUSHBACK-
				//if (!failed)
					//drawBuffer.push_back(t);
				
				drawBuffer3D.push_back(tri);
			//--
		}
	}
	else // khm todo: abstract class for point groups -> then line strip
	{

	}
}

void Camera::drawGameObject(GameObject& go)
{
	
	Transform t = go.getTransform();
	Mesh mesh = t.applyTransform(go.getMesh());
	unsigned int vao;
	//std::vector<Triangle3D> triangles = std::vector<Triangle3D>();

	// loads vertices

	//for (size_t i = 0; i < mesh.getIndexBufferSize() - 2; i += 3)
	//{
	//	int iterator = static_cast<int>(i);
	//	int sol = iterator / 3;
	//	size_t vo = 0; // every third vertex
	//	if (sol < mesh.getTriCount())
	//		vo = sol; //size_t scam 

	//	int normalIndex = mesh.shareNormalIndex()[vo]; // get the normal buffer index


	//	Triangle3D tri = Triangle3D(
	//		mesh.loadVertex(mesh.shareIndex()[i] - 1),
	//		mesh.loadVertex(mesh.shareIndex()[i + 1] - 1),
	//		mesh.loadVertex(mesh.shareIndex()[i + 2] - 1),
	//		mesh.loadBakedMaterial(mesh.shareIndex()[i] - 1),
	//		mesh.loadBakedMaterial(mesh.shareIndex()[i + 1] - 1),
	//		mesh.loadBakedMaterial(mesh.shareIndex()[i + 2] - 1)); 
	//	
	//	Vector3D normal = mesh.loadNormal(normalIndex - 1); // normalbuffer stores normal vectors/face
	//		if (normal.dot(focuspoint - tri.getWpoint()) < 0)
	//			continue;


	//	triangles.push_back(tri); // extract a triangle from the vertex array
	//
	//}
	//double* vertices = new double[triangles.size() * 9];
	//double* materials = new double[triangles.size() * 9];

	//for (size_t i = 0; i < triangles.size();i++)
	//{
	//	vertices[i*9] = triangles[i].getV1().getX();
	//	vertices[i*9+1] = triangles[i].getV1().getY();
	//	vertices[i*9+2] = triangles[i].getV1().getZ();
	//	vertices[i * 9+ 3] = triangles[i].getV2().getX();
	//	vertices[i * 9 + 4] = triangles[i].getV2().getY();
	//	vertices[i * 9 + 5] = triangles[i].getV2().getZ();
	//	vertices[i * 9 + 6] = triangles[i].getV3().getX();
	//	vertices[i * 9 + 7] = triangles[i].getV3().getY();
	//	vertices[i * 9 + 8] = triangles[i].getV3().getZ();

	//}

	int* indices = new int[mesh.getIndexBufferSize()];

	for (size_t i = 0; i < mesh.getIndexBufferSize(); i++)
	{
		indices[i] = mesh.shareIndex()[i]-1;
	}

	// BINDING THE INDEX BUFFER
	glGenBuffers(1, &m_shaderProgram);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_shaderProgram); //bind the buffer (set the "state machine")
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndexBufferSize() * sizeof(GLuint), indices, GL_DYNAMIC_DRAW); //write data to buffer (gluint is the correct OPENGL size)

	double* vertices = new double[mesh.getVertexCount()*3];

	// GETTING THE VERTICES
	for (size_t i = 0; i < mesh.getVertexCount();i++)
	{
		vertices[i*3] = mesh.loadVertex(i).getX();
		vertices[i * 3+1] = mesh.loadVertex(i).getY();
		vertices[i * 3+2] = mesh.loadVertex(i).getZ();
	}

	// BINDING THE VBO
	glGenBuffers(1, &m_shaderProgram); //create a buffer with "buffer" id
	glBindBuffer(GL_ARRAY_BUFFER, m_shaderProgram); //bind the buffer (set the "state machine")
	glBufferData(GL_ARRAY_BUFFER, mesh.getVertexCount()*3*sizeof(double), vertices, GL_DYNAMIC_DRAW); //write data to buffer



	// bind them

	//glGenVertexArrays(1, &vao);	// get 1 vao id
	//glBindVertexArray(vao);		// make it active

	//unsigned int vbo;		// vertex buffer object
	//glGenBuffers(1, &vbo);	// Generate 1 buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//glBufferData(GL_ARRAY_BUFFER, 	// Copy to GPU target
	//	sizeof(double) * triangles.size() * 9,  // # bytes
	//	vertices,	      	// address
	//	GL_DYNAMIC_DRAW);	// we do not change later

	glEnableVertexAttribArray(0);  // AttribArray 0
	glVertexAttribPointer(0,       // vbo -> AttribArray 0
		3, GL_DOUBLE, GL_FALSE, // three floats/attrib, not fixed-point
		0, NULL); 		     // stride, offset: tightly packed

	//glEnableVertexAttribArray(1);  // AttribArray 0
	//glVertexAttribPointer(1,       // vbo -> AttribArray 0
	//	3, GL_DOUBLE, GL_FALSE, // three floats/attrib, not fixed-point
	//	0, NULL); 		     // stride, offset: tightly packed


	/*GLint posAttrib = glGetAttribLocation(m_shaderProgram, "vp");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_DOUBLE, GL_FALSE, 0, NULL);

	GLint colAttrib = glGetAttribLocation(m_shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLdouble), (void*)(2 * sizeof(GLfloat)));*/


	// draw

	glUseProgram(m_shaderProgram);

	/*double pitch = t.getPitch();
	double yaw = t.getYaw();
	Vector3D goPos = t.getPos();

	mat4 scale = mat4(
		vec4(0.001, 0, 0, 0),
		vec4(0, 0.001, 0, 0),
		vec4(0, 0, 0.001, 0),
		vec4(0, 0, 0, 1));

	mat4 rot = mat4(
		vec4(cos(yaw) * cos(pitch), sin(yaw) * cos(pitch), sin(pitch), 0),
		vec4(-sin(yaw), cos(yaw), 0, 0),
		vec4(-cos(yaw) * sin(pitch), -sin(yaw) * sin(pitch), cos(pitch), 0),
		vec4(0, 0, 0, 1));

	mat4 pos = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(goPos.getX(), goPos.getY(), goPos.getZ(), 1));

	mat4 model = scale * rot * pos;*/
	//double* mp = &(model[0][0]);

	//float MVPtransf[4][4] = { 1, 0, 0, 0,    // MVP matrix, 
	//						  0, 1, 0, 0,    // row-major!
	//						  0, 0, 1, 0,
	//						  0, 0, 0, 1 };

	//for (int i = 0; i < 4; i++)
	//	for (int j = 0; j < 4; j++)
	//		MVPtransf[i][j] = model[i][j];

	

	glMatrixMode(GL_PROJECTION); // projection matrix for "3d"
	glLoadIdentity();
	gluPerspective(90, (float)1024 / (float)764, 0.01f, 1000000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Vector3D front = transform.getRot().getI().normalize()+focuspoint;
	Vector3D up = transform.getRot().getK();
	gluLookAt(focuspoint.getX(), focuspoint.getY(), focuspoint.getZ(),
		front.getX(), front.getY(), front.getZ(),
		up.getX(), up.getY(), up.getZ()); // view matrix (camara rotation)

	glBindVertexArray(m_shaderProgram);  // Draw call
	//glDrawArrays(GL_TRIANGLES, 0 /*startIdx*/, triangles.size()*3 /*# Elements*/);
	glDrawElements(GL_TRIANGLES, mesh.getIndexBufferSize(), GL_UNSIGNED_INT, nullptr);
	//int location = glGetUniformLocation(m_shaderProgram, "MVP");	// Get the GPU location of uniform variable MVP
	//glUniformMatrix4dv(location, 1, GL_TRUE, mp);	// Load a 4x4 row-major float matrix to the specified location




	glDeleteBuffers(1, &m_shaderProgram); // delete vertex buffer, and index (element) buffer
	glDeleteVertexArrays(1, &m_shaderProgram); //delete vao
	


	glBindBuffer(GL_ARRAY_BUFFER, 0); //clear vbo?
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0); //clear vao
	glUseProgram(0);


	delete[] vertices;
	delete[] indices;
}
