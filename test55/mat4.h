#include "vec4.h"

class mat4
{
	vec4 rows[4];

public:
	mat4(){}

	mat4(vec4 v0, vec4 v1, vec4 v2, vec4 v3)
	{
		rows[0] = v0;
		rows[1] = v1;
		rows[2] = v2;
		rows[3] = v3;

	}

	vec4& operator[](int i) { return rows[i]; }
	vec4 operator[](int i) const { return rows[i]; }
	operator float*() const { return (float*)this; }

};


inline vec4 operator*(const vec4& v, const mat4& mat) {
	return v[0] * mat[0] + v[1] * mat[1] + v[2] * mat[2] + v[3] * mat[3];
}

inline mat4 operator*(const mat4& left, const mat4& right) {
	mat4 result;
	for (int i = 0; i < 4; i++) result[i] = left[i] * right;
	return result;
}