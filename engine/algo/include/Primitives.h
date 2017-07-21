#pragma once
#include <math.h>

#define M_PI       3.14159265358979323846   // pi

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

struct Quaternion
{
	float x, y, z, w;

	Quaternion()
	{
		x = 0; y = 0; z = 0; w = 0;
	}

	Quaternion(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Normalize()
	{
		float Length = sqrtf(x * x + y * y + z * z + w * w);
		x /= Length;
		y /= Length;
		z /= Length;
		w /= Length;
	}

	Quaternion Conjugate()
	{
		Quaternion ret(-x, -y, -z, w);
		return ret;
	}
};

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

	Vector3f Vector3f::Cross(const Vector3f& v) const
	{
		const float _x = y * v.z - z * v.y;
		const float _y = z * v.x - x * v.z;
		const float _z = x * v.y - y * v.x;

		return Vector3f(_x, _y, _z);
	}

	Vector3f& Vector3f::Normalize()
	{
		const float Length = sqrtf(x * x + y * y + z * z);

		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}

	void Vector3f::Rotate(float Angle, const Vector3f& Axe)
	{
		const float SinHalfAngle = sinf(ToRadian(Angle / 2));
		const float CosHalfAngle = cosf(ToRadian(Angle / 2));

		const float Rx = Axe.x * SinHalfAngle;
		const float Ry = Axe.y * SinHalfAngle;
		const float Rz = Axe.z * SinHalfAngle;
		const float Rw = CosHalfAngle;
		Quaternion RotationQ(Rx, Ry, Rz, Rw);
		Quaternion ConjugateQ = RotationQ.Conjugate();
		//  ConjugateQ.Normalize();
		Quaternion W;// = RotationQ * (*this) * ConjugateQ;

		W.w = -(RotationQ.x * x) - (RotationQ.y * y) - (RotationQ.z * z);
		W.x = (RotationQ.w * x) + (RotationQ.y * z) - (RotationQ.z * y);
		W.y = (RotationQ.w * y) + (RotationQ.z * x) - (RotationQ.x * z);
		W.z = (RotationQ.w * z) + (RotationQ.x * y) - (RotationQ.y * x);
		W.w = (W.w * ConjugateQ.w) - (W.x * ConjugateQ.x) - (W.y * ConjugateQ.y) - (W.z * ConjugateQ.z);
		W.x = (W.x * ConjugateQ.w) + (W.w * ConjugateQ.x) + (W.y * ConjugateQ.z) - (W.z * ConjugateQ.y);
		W.y = (W.y * ConjugateQ.w) + (W.w * ConjugateQ.y) + (W.z * ConjugateQ.x) - (W.x * ConjugateQ.z);
		W.z = (W.z * ConjugateQ.w) + (W.w * ConjugateQ.z) + (W.x * ConjugateQ.y) - (W.y * ConjugateQ.x);

		x = W.x;
		y = W.y;
		z = W.z;
	}

	//TODO: add move constructor
	void operator=(Vector3f right) 
	{
		x = right.x;
		y = right.y;
		z = right.z;
	}

	Vector3f& operator+=(const Vector3f& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}

	Vector3f& operator-=(const Vector3f& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}

	Vector3f& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}
};

inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);
	return Ret;
}

inline Vector3f operator*(const Vector3f& l, float f)
{
	Vector3f Ret(l.x * f,
		l.y * f,
		l.z * f);
	return Ret;
}

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

	void Matrix4f::InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
	{
		matrix[0][0] = ScaleX; matrix[0][1] = 0.0f;   matrix[0][2] = 0.0f;   matrix[0][3] = 0.0f;
		matrix[1][0] = 0.0f;   matrix[1][1] = ScaleY; matrix[1][2] = 0.0f;   matrix[1][3] = 0.0f;
		matrix[2][0] = 0.0f;   matrix[2][1] = 0.0f;   matrix[2][2] = ScaleZ; matrix[2][3] = 0.0f;
		matrix[3][0] = 0.0f;   matrix[3][1] = 0.0f;   matrix[3][2] = 0.0f;   matrix[3][3] = 1.0f;
	}

	void Matrix4f::InitRotateTransform(float RotateX, float RotateY, float RotateZ)
	{
		Matrix4f rx, ry, rz;
		const float x = ToRadian(RotateX);
		const float y = ToRadian(RotateY);
		const float z = ToRadian(RotateZ);
		rx[0][0] = 1.0f; rx[0][1] = 0.0f; rx[0][2] = 0.0f; rx[0][3] = 0.0f;
		rx[1][0] = 0.0f; rx[1][1] = cosf(x); rx[1][2] = -sinf(x); rx[1][3] = 0.0f;
		rx[2][0] = 0.0f; rx[2][1] = sinf(x); rx[2][2] = cosf(x); rx[2][3] = 0.0f;
		rx[3][0] = 0.0f; rx[3][1] = 0.0f; rx[3][2] = 0.0f; rx[3][3] = 1.0f;

		ry[0][0] = cosf(y); ry[0][1] = 0.0f; ry[0][2] = -sinf(y); ry[0][3] = 0.0f;
		ry[1][0] = 0.0f; ry[1][1] = 1.0f; ry[1][2] = 0.0f; ry[1][3] = 0.0f;
		ry[2][0] = sinf(y); ry[2][1] = 0.0f; ry[2][2] = cosf(y); ry[2][3] = 0.0f;
		ry[3][0] = 0.0f; ry[3][1] = 0.0f; ry[3][2] = 0.0f; ry[3][3] = 1.0f;

		rz[0][0] = cosf(z); rz[0][1] = -sinf(z); rz[0][2] = 0.0f; rz[0][3] = 0.0f;
		rz[1][0] = sinf(z); rz[1][1] = cosf(z); rz[1][2] = 0.0f; rz[1][3] = 0.0f;
		rz[2][0] = 0.0f; rz[2][1] = 0.0f; rz[2][2] = 1.0f; rz[2][3] = 0.0f;
		rz[3][0] = 0.0f; rz[3][1] = 0.0f; rz[3][2] = 0.0f; rz[3][3] = 1.0f;
		*this = rz * ry * rx;
	}



	void Matrix4f::InitTranslationTransform(float x, float y, float z)
	{
		matrix[0][0] = 1.0f; matrix[0][1] = 0.0f; matrix[0][2] = 0.0f; matrix[0][3] = x;
		matrix[1][0] = 0.0f; matrix[1][1] = 1.0f; matrix[1][2] = 0.0f; matrix[1][3] = y;
		matrix[2][0] = 0.0f; matrix[2][1] = 0.0f; matrix[2][2] = 1.0f; matrix[2][3] = z;
		matrix[3][0] = 0.0f; matrix[3][1] = 0.0f; matrix[3][2] = 0.0f; matrix[3][3] = 1.0f;
	}

	void Matrix4f::InitCameraTransform(const Vector3f& Target, const Vector3f& Up)
	{
		Vector3f N = Target;
		N.Normalize();
		Vector3f U = Up;
		U.Normalize();
		U = U.Cross(N);
		Vector3f V = N.Cross(U);
		matrix[0][0] = U.x;   matrix[0][1] = U.y;   matrix[0][2] = U.z;   matrix[0][3] = 0.0f;
		matrix[1][0] = V.x;   matrix[1][1] = V.y;   matrix[1][2] = V.z;   matrix[1][3] = 0.0f;
		matrix[2][0] = N.x;   matrix[2][1] = N.y;   matrix[2][2] = N.z;   matrix[2][3] = 0.0f;
		matrix[3][0] = 0.0f;  matrix[3][1] = 0.0f;  matrix[3][2] = 0.0f;  matrix[3][3] = 1.0f;
	}

	void Matrix4f::InitPersProjTransform(float FOV, float Width, float Height, float zNear, float zFar)
	{
		const float ar = Width / Height;
		const float zRange = zNear - zFar;
		const float tanHalfFOV = tanf(ToRadian(FOV / 2.0f));
		matrix[0][0] = 1.0f / (tanHalfFOV * ar); 
		matrix[0][1] = 0.0f;            
		matrix[0][2] = 0.0f;          
		matrix[0][3] = 0.0;

		matrix[1][0] = 0.0f;                  
		matrix[1][1] = 1.0f / tanHalfFOV;
		matrix[1][2] = 0.0f;         
		matrix[1][3] = 0.0;

		matrix[2][0] = 0.0f;                   
		matrix[2][1] = 0.0f;            
		matrix[2][2] = (-zNear - zFar) / zRange;
		matrix[2][3] = 2.0f * zFar*zNear / zRange;

		matrix[3][0] = 0.0f;                  
		matrix[3][1] = 0.0f;          
		matrix[3][2] = 1.0f;        
		matrix[3][3] = 0.0;
	}
};