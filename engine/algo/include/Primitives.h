#pragma once


#define M_PI       3.14159265358979323846   // pi

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

struct Vector2f
{
	float x;
	float y;

	Vector2f() : x(0), y(0)
	{
	}

	Vector2f(float _x, float _y) : x(_x), y(_y)
	{
	}

	void operator=(Vector2f right) {
		x = right.x;
		y = right.y;
	}

};

struct Vector3f
{
	float x;
	float y;
	float z;

	Vector3f() : x(0), y(0), z(0)
	{
	}

	Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{
	}

	//TODO: add move constructor
	void operator=(Vector3f right) {
		x = right.x;
		y = right.y;
		z = right.z;
	}

};

struct Matrix4f {
private:
	float matrix[4][4];
public:
	Matrix4f() {
		setIdentity();
	}

	void setIdentity() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (i == j) matrix[i][j] = 1;
				else matrix[i][j] = 0;
			}
	}


	float* operator[](int index) {
		return matrix[index];
	}

	Matrix4f operator*(Matrix4f& right)
	{
		Matrix4f res;

		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = 0; j < 4; j++) {
				res[i][j] = matrix[i][0] * right[0][j] +
					matrix[i][1] * right[1][j] +
					matrix[i][2] * right[2][j] +
					matrix[i][3] * right[3][j];
			}
		}

		return res;
	}

	Vector3f operator*(Vector3f& right)
	{
		Vector3f res;
		float scale;
		res.x = matrix[0][0] * right.x +
			matrix[0][1] * right.y +
			matrix[0][2] * right.z +
			matrix[0][3] * 1;
		res.y = matrix[1][0] * right.x +
			matrix[1][1] * right.y +
			matrix[1][2] * right.z +
			matrix[1][3] * 1;
		res.z = matrix[2][0] * right.x +
			matrix[2][1] * right.y +
			matrix[2][2] * right.z +
			matrix[2][3] * 1;
		scale = matrix[3][0] * right.x +
			matrix[3][1] * right.y +
			matrix[3][2] * right.z +
			matrix[3][3] * 1;
		res.x /= scale;
		res.y /= scale;
		res.z /= scale;
		return res;
	}

};