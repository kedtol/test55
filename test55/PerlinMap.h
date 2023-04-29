class PerlinMap
{
	int w;
	int h;
	Vector2D* perlin = new Vector2D[w * h];

	PerlinMap();
	~PerlinMap() { delete perlin; }
};