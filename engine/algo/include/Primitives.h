#pragma once
#include <math.h>

#define M_PI       3.14159265358979323846   // pi

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

struct Vector3f;

struct Quaternion
{
	float x, y, z, w;
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

	Vector2f& operator+=(const Vector2f& r)
	{
		x += r.x;
		y += r.y;
		return *this;
	}

	Vector2f& operator-=(const Vector2f& r)
	{
		x -= r.x;
		y -= r.y;
		return *this;
	}

	Vector2f& operator*=(float f)
	{
		x *= f;
		y *= f;
		return *this;
	}

};

inline Vector2f operator-(const Vector2f& l, const Vector2f& r)
{
	Vector2f Ret(l.x - r.x,
		l.y - r.y);
	return Ret;
}

inline Vector2f operator+(const Vector2f& l, const Vector2f& r)
{
	Vector2f Ret(l.x + r.x,
		l.y + r.y);
	return Ret;
}

inline Vector2f operator*(const Vector2f& l, float f)
{
	Vector2f Ret(l.x * f,
		l.y * f);
	return Ret;
}

inline Vector2f operator/(const Vector2f& l, float f)
{
	Vector2f Ret(l.x / f,
		l.y / f);
	return Ret;
}

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

	Vector3f Cross(const Vector3f& v) const
	{
		const float _x = y * v.z - z * v.y;
		const float _y = z * v.x - x * v.z;
		const float _z = x * v.y - y * v.x;

		return Vector3f(_x, _y, _z);
	}

	Vector3f& Normalize()
	{
		const float Length = sqrtf(x * x + y * y + z * z);

		x /= Length;
		y /= Length;
		z /= Length;

		return *this;
	}

	void Rotate(float Angle, const Vector3f& Axe)
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
		//Quaternion W = RotationQ * (*this) * ConjugateQ;
		Quaternion W = Quaternion(0,0,0,0);

		W.w = -(RotationQ.x * (*this).x) - (RotationQ.y * (*this).y) - (RotationQ.z * (*this).z);
		W.x = (RotationQ.w * (*this).x) + (RotationQ.y * (*this).z) - (RotationQ.z * (*this).y);
		W.y = (RotationQ.w * (*this).y) + (RotationQ.z * (*this).x) - (RotationQ.x * (*this).z);
		W.z = (RotationQ.w * (*this).z) + (RotationQ.x * (*this).y) - (RotationQ.y * (*this).x);

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

inline bool operator==(const Vector3f& l, const Vector3f& r)
{
	if (l.x != r.x || l.y != r.y || l.z != r.z) return false;
	return true;
}

inline bool operator!=(const Vector3f& l, const Vector3f& r) 
{
	return !(l == r); 
}

inline Vector3f operator-(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x - r.x,
		l.y - r.y,
		l.z - r.z);
	return Ret;
}

inline Vector3f operator+(const Vector3f& l, const Vector3f& r)
{
	Vector3f Ret(l.x + r.x,
		l.y + r.y,
		l.z + r.z);
	return Ret;
}

inline Vector3f operator*(const Vector3f& l, float f)
{
	Vector3f Ret(l.x * f,
		l.y * f,
		l.z * f);
	return Ret;
}

struct Vertex
{
	Vector3f pos;
	Vector2f tex;
	Vector3f norm;
	Vertex() {}
	Vertex(Vector3f _pos, Vector2f _tex) : pos(_pos), tex(_tex), norm(Vector3f(0.0f, 0.0f, 0.0f))
	{
	}
};

inline void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount, Vertex* pVertices, unsigned int VertexCount)
{
	for (unsigned int i = 0; i < VertexCount; i++)
	{
		pVertices[i].norm.x = 0.0f;
		pVertices[i].norm.y = 0.0f;
		pVertices[i].norm.z = 0.0f;
	}
	for (unsigned int i = 0; i < IndexCount; i += 3) 
	{
		unsigned int Index0 = pIndices[i];
		unsigned int Index1 = pIndices[i + 1];
		unsigned int Index2 = pIndices[i + 2];
		Vector3f v1 = pVertices[Index1].pos - pVertices[Index0].pos;
		Vector3f v2 = pVertices[Index2].pos - pVertices[Index0].pos;
		Vector3f Normal = v1.Cross(v2);
		Normal.Normalize();

		pVertices[Index0].norm += Normal;
		pVertices[Index1].norm += Normal;
		pVertices[Index2].norm += Normal;
	}

	for (unsigned int i = 0; i < VertexCount; i++) {
		pVertices[i].norm.Normalize();
	}
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

	void InitScaleTransform(float ScaleX, float ScaleY, float ScaleZ)
	{
		matrix[0][0] = ScaleX; matrix[0][1] = 0.0f;   matrix[0][2] = 0.0f;   matrix[0][3] = 0.0f;
		matrix[1][0] = 0.0f;   matrix[1][1] = ScaleY; matrix[1][2] = 0.0f;   matrix[1][3] = 0.0f;
		matrix[2][0] = 0.0f;   matrix[2][1] = 0.0f;   matrix[2][2] = ScaleZ; matrix[2][3] = 0.0f;
		matrix[3][0] = 0.0f;   matrix[3][1] = 0.0f;   matrix[3][2] = 0.0f;   matrix[3][3] = 1.0f;
	}

	void InitRotateTransform(float RotateX, float RotateY, float RotateZ)
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



	void InitTranslationTransform(float x, float y, float z)
	{
		matrix[0][0] = 1.0f; matrix[0][1] = 0.0f; matrix[0][2] = 0.0f; matrix[0][3] = x;
		matrix[1][0] = 0.0f; matrix[1][1] = 1.0f; matrix[1][2] = 0.0f; matrix[1][3] = y;
		matrix[2][0] = 0.0f; matrix[2][1] = 0.0f; matrix[2][2] = 1.0f; matrix[2][3] = z;
		matrix[3][0] = 0.0f; matrix[3][1] = 0.0f; matrix[3][2] = 0.0f; matrix[3][3] = 1.0f;
	}

	void InitCameraTransform(const Vector3f& Target, const Vector3f& Up)
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

	void InitOrthoProjTransform(float Width, float Height, float zNear, float zFar)
	{
		const float ar = Width / Height;
		const float zRange = zNear - zFar;
		matrix[0][0] = 2.0f / ar;
		matrix[0][1] = 0.0f;
		matrix[0][2] = 0.0f;
		matrix[0][3] = -1.0f;

		matrix[1][0] = 0.0f;
		matrix[1][1] = -2.0f;
		matrix[1][2] = 0.0f;
		matrix[1][3] = 1.0f;

		matrix[2][0] = 0.0f;
		matrix[2][1] = 0.0f;
		matrix[2][2] = 2.0f / zRange;
		matrix[2][3] = 0.0f;

		matrix[3][0] = 0.0f;
		matrix[3][1] = 0.0f;
		matrix[3][2] = 0.0f;
		matrix[3][3] = 1.0f;
	}

	void InitPersProjTransform(float FOV, float Width, float Height, float zNear, float zFar)
	{
		const float ar = Width / Height;
		const float zRange = zNear - zFar;
		const float tanHalfFOV = tanf(ToRadian(FOV / 2.0f));
		matrix[0][0] = 1.0f / (tanHalfFOV * ar); 
		matrix[0][1] = 0.0f;            
		matrix[0][2] = 0.0f;          
		matrix[0][3] = 0.0f;

		matrix[1][0] = 0.0f;                  
		matrix[1][1] = 1.0f / tanHalfFOV;
		matrix[1][2] = 0.0f;         
		matrix[1][3] = 0.0f;

		matrix[2][0] = 0.0f;                   
		matrix[2][1] = 0.0f;            
		matrix[2][2] = (-zNear - zFar) / zRange;
		matrix[2][3] = 2.0f * zFar*zNear / zRange;

		matrix[3][0] = 0.0f;                  
		matrix[3][1] = 0.0f;          
		matrix[3][2] = 1.0f;        
		matrix[3][3] = 0.0f;
	}

	void InitBiasMatrix()
	{
		matrix[0][0] = 0.5f;
		matrix[0][1] = 0.0f;
		matrix[0][2] = 0.0f;
		matrix[0][3] = 0.5f;

		matrix[1][0] = 0.0f;
		matrix[1][1] = 0.5f;
		matrix[1][2] = 0.0f;
		matrix[1][3] = 0.5f;

		matrix[2][0] = 0.0f;
		matrix[2][1] = 0.0f;
		matrix[2][2] = 0.5f;
		matrix[2][3] = 0.5f;

		matrix[3][0] = 0.0f;
		matrix[3][1] = 0.0f;
		matrix[3][2] = 0.0f;
		matrix[3][3] = 1.0f;
	}
};
