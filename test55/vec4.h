#pragma once
class vec4
{
	double x, y, z, w;

public:
	vec4(){}

	vec4(double _x , double _y, double _z, double _w) 
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	double& operator[](int i) { return *(&x + i); }
	double operator[](int i) const { return *(&x + i); }
	vec4 operator*(double a) const { return vec4(x * a, y * a, z * a, w * a); }
	vec4 operator+(vec4 a) const { return vec4(x + a.x, y + a.y, z + a.z, w + a.w); }
	vec4 operator-(vec4 a) const { return vec4(x - a.x, y - a.y, z - a.z, w - a.w); }
	void operator+=(const vec4 a) { x += a.x; y += a.y; z += a.z; w += a.w; }
};

inline vec4 operator*(float a, const vec4& v) {
	return vec4(v[0] * a, v[1] * a, v[2] * a, v[3] * a);
}

inline float dot(const vec4& v1, const vec4& v2) {
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3]);
}