#pragma once
#include "GLIncludes.h"
#include "Primitives.h"

class MatrixHelper {
private:
	Matrix4f _matrix;
	Matrix4f _position;
	Matrix4f _rotate;
	Matrix4f _scale;
	Matrix4f _persProj;

public:
	void setRotate(const Vector3f& rotate);
	Matrix4f& getRotation();
	void setBackRotate(const Vector3f& rotate);
	void setScale(const Vector3f& scale);
	Matrix4f& getScale();
	void setPosition(const Vector3f& position);
	Matrix4f& getTranslation();
	void setPerspective(float FOV, float width, float height, float znear, float zfar);
	Matrix4f& getPerspective();
	Matrix4f& getMatrix();
};