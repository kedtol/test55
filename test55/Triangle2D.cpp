#include "Triangle2D.h"

Triangle2D::Triangle2D(Vector2D _v1, Vector2D _v2, Vector2D _v3, Material _m, Material _m1, Material _m2, double _d)
{
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	m = _m;
	m1 = _m1;
	m2 = _m2;
	d = _d;
}

void Triangle2D::draw(SDL_Renderer* renderer)
{
	double screenw = 512;
	double screenh = 384;

	Vector2D screen1 = Vector2D(0, 0);
	Vector2D screen2 = Vector2D(screenw, screenh);

	//after casting CLIPPING 
	bool v1out = !v1.insideRect(screen1, screen2);
	bool v2out = !v2.insideRect(screen1, screen2);
	bool v3out = !v3.insideRect(screen1, screen2);

	/*for (int i = 1; i < polygon.size() + 1; i++)
	{
		vx[i] = polygon[i-1].getX();
		vy[i] = polygon[i - 1].getY();
	}*/
	if (!v1out && !v2out && !v3out)
		filledTrigonRGBA(renderer, v1.getX(), v1.getY(), v2.getX(), v2.getY(), v3.getX(), v3.getY(), m.getR(), m.getG(), m.getB(), 255);
	else
	{
		//rectangleRGBA(renderer, screen1.getX(), screen1.getY(), screen2.getX(), screen2.getY(), m.getR(), m.getG(), m.getB(), 255);

		/*bool failed = false;
		Line2D la = Line2D(v2, v1 - v2, v1, v2);
		Line2D lb = Line2D(v3, v2 - v3, v2, v3);
		Line2D lc = Line2D(v1, v3 - v1, v3, v1);

		Vector2D* ait1p = NULL;
		Vector2D* ait2p = NULL;
		Vector2D* bit1p = NULL;
		Vector2D* bit2p = NULL;
		Vector2D* cit1p = NULL;
		Vector2D* cit2p = NULL;
		if (v1out || v2out)
			la.rectIntersection(screen1, screen2, &ait1p, &ait2p);
		if (v2out || v3out)
			lb.rectIntersection(screen1, screen2, &bit1p, &bit2p);
		if (v3out || v1out)
			lc.rectIntersection(screen1, screen2, &cit1p, &cit2p);

		std::vector<Vector2D> polygon;

		if (bit1p != NULL)
			polygon.push_back(*bit1p);

		if (bit2p != NULL)
			polygon.push_back(*bit2p);

		if (!v3out)
			polygon.push_back(v3);
		if (cit1p != NULL)
			polygon.push_back(*cit1p);
		if (cit2p != NULL)
			polygon.push_back(*cit2p);

		if (!v1out)
			polygon.push_back(v1);
		if (ait1p != NULL)
			polygon.push_back(*ait1p);
		if (ait2p != NULL)
			polygon.push_back(*ait2p);
		if (!v2out)
			polygon.push_back(v2);
		if (ait1p != NULL)
			polygon.push_back(*ait1p);
		if (ait2p != NULL)
			polygon.push_back(*ait2p);

		Vector2D wpoint = Vector2D();

		for (int i = 0; i < polygon.size(); i++)
			wpoint += polygon[i];

		double num = 1. / polygon.size();
		wpoint = wpoint * num;

		polygon.push_back(wpoint);

		for (int i = 0; i < polygon.size(); i++)
		{
			Vector2D o1;
			Vector2D o2;
			Vector2D o3;

			o1 = polygon[i];
			if (i + 1 < polygon.size())
			{
				o2 = polygon[i + 1];
			}
			else
			{
				o2 = polygon[0];
			}
			o3 = wpoint;
			filledTrigonRGBA(renderer, o1.getX(), o1.getY(), o2.getX(), o2.getY(), o3.getX(), o3.getY(), m.getR(), m.getG(), m.getB(), 255);
		}
		polygon.clear();

		delete ait1p;
		delete ait2p;
		delete bit1p;
		delete bit2p;
		delete cit1p;
		delete cit2p;*/
	}
		
	//stringRGBA(renderer, v1.getX(), v1.getY(), "v1", 0, 255, 0, 255);
	//stringRGBA(renderer, v2.getX(), v2.getY(), "v2", 0, 255, 255, 255);
	//stringRGBA(renderer, v3.getX(), v3.getY(), "v3", 0, 0, 255, 255);
	//for (int i = 0; i < polygon.size(); i++)
		//boxRGBA(renderer, polygon[i].getX(), polygon[i].getY(), polygon[i].getX() + 5, polygon[i].getY() + 5, 255/(i+1), 200, 200, 255);

	
		//filledPolygonRGBA(renderer, vx, vy, polygon.size(), m.getR(), m.getG(), m.getB(),255);

	

	//if (v1.getX() > 0 && v2.getX() > 0 && v3.getX() > 0 && v1.getY() > 0 && v2.getY() > 0 && v3.getY() > 0)
	//	if (v1.getX() < screenw && v2.getX() < screenw && v3.getX() < screenw && v1.getY() < screenh && v2.getY() < screenh && v3.getY() < screenh)
	//		filledTrigonRGBA(renderer, v1.getX(), v1.getY(), v2.getX(), v2.getY(), v3.getX(), v3.getY(), m.getR(), m.getG(), m.getB(), 255);
	//rectangleRGBA(renderer, v1.getX(), v1.getY(), v3.getX(), v3.getY(), m.getR(), m.getG(), m.getB(), 255);
}

void Triangle2D::render(SDL_GLContext* gcontext)
{
	
	double screenw = 1024./2.;
	double screenh = 768./2.;

	Vector2D screen1 = Vector2D(0, 0);
	Vector2D screen2 = Vector2D(screenw, screenh);

	bool v1out = !v1.insideRect(screen1, screen2);
	bool v2out = !v2.insideRect(screen1, screen2);
	bool v3out = !v3.insideRect(screen1, screen2);

	//if (!v1out && !v2out && !v3out)
	//{
	//}

		glBegin(GL_TRIANGLES);
		
		Vector2D v1_ = v1.castGL(screen2);
		
		Vector2D v2_ = v2.castGL(screen2);
		
		Vector2D v3_ = v3.castGL(screen2);
		
		glColor4b(m.getR() - 128, m.getG() - 128, m.getB() - 128, 128);
		glVertex2f(v1_.getX(), v1_.getY());
		
		glColor4b(m1.getR() - 128, m1.getG() - 128, m1.getB() - 128, 128);

		glVertex2f(v2_.getX(), v2_.getY());
		glColor4b(m2.getR() - 128, m2.getG() - 128, m2.getB() - 128, 128);

		glVertex2f(v3_.getX(), v3_.getY());
		glEnd();
	
		// LINE -> POINT RASTER (VERY INEFFICIENT)
		/*Vector2D a = v1 - v2;
		for (double i = 0; i < 1; i += 0.05)
		{
			Vector2D a_i = (v2 + (a * i));
			SDL_SetRenderDrawColor(renderer, m.getR(), m.getG(), m.getB(), 255);
			SDL_RenderDrawLine(renderer, a_i.getX(), a_i.getY(), v3.getX(), v3.getY());
		}*/

		// PIXEL BY PIXEL RASTER (THE MOST INEFFICIENT?)
		/*Vector2D a = v1 - v2;
		Vector2D b = v1 - v3;
		double iteration = 0.1;
		for (double i = 0; i < 1; i += iteration)
		{
			for (double j = 0; j < 1; j += iteration)
			{
				Vector2D a_i = (v2 + (a * i));
				Vector2D b_i = (v3 + (b * i));
				Vector2D ab = b_i - a_i;
				Vector2D ab_i = (a_i + (ab * j));
			
				//SDL_SetRenderDrawColor(renderer, m.getR(), m.getG(), m.getB(), 255);
				// i could add some cool shading here (if i had a material for each vertex)
				SDL_RenderDrawPoint(renderer, ab_i.getX(), ab_i.getY());
				
			}
		}*/
		
		/*Vector2D box0;
		Vector2D box1;
		if (v1.getX() < v2.getX() && v1.getX() < v3.getX())
			box0 = Vector2D(v1.getX(), 0);
		if (v2.getX() < v1.getX() && v2.getX() < v3.getX())
			box0 = Vector2D(v2.getX(), 0);
		if (v3.getX() < v1.getX() && v3.getX() < v2.getX())
			box0 = Vector2D(v3.getX(), 0);

		if (v1.getY() < v2.getY() && v1.getY() < v3.getY())
			box0 = Vector2D(box0.getX(), v1.getY());
		if (v2.getY() < v1.getY() && v2.getY() < v3.getY())
			box0 = Vector2D(box0.getX(), v2.getY());
		if (v3.getY() < v1.getY() && v3.getY() < v2.getY())
			box0 = Vector2D(box0.getX(), v3.getY());

		if (v1.getX() > v2.getX() && v1.getX() > v3.getX())
			box1 = Vector2D(v1.getX(), 0);
		if (v2.getX() > v1.getX() && v2.getX() > v3.getX())
			box1 = Vector2D(v2.getX(), 0);
		if (v3.getX() > v1.getX() && v3.getX() > v2.getX())
			box1 = Vector2D(v3.getX(), 0);

		if (v1.getY() > v2.getY() && v1.getY() > v3.getY())
			box1 = Vector2D(box1.getX(), v1.getY());
		if (v2.getY() > v1.getY() && v2.getY() > v3.getY())
			box1 = Vector2D(box1.getX(), v2.getY());
		if (v3.getY() > v1.getY() && v3.getY() > v2.getY())
			box1 = Vector2D(box1.getX(), v3.getY());

		Vector2D a = v1 - v2;
		Vector2D b = v1 - v3;
		double dotprod = a.dot(b);

		for (size_t i = box0.getX(); i < box1.getX(); i ++)
		{
			for (size_t j = box0.getY(); j < box1.getY(); j ++)
			{
				SDL_SetRenderDrawColor(renderer, m.getR(), m.getG(), m.getB(), 255);
				SDL_RenderDrawPoint(renderer, i, j);

			}
		}*/

	

}

