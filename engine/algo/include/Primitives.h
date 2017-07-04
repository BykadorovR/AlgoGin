#pragma once


#define M_PI       3.14159265358979323846   // pi

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)


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

};