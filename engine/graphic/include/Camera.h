#pragma once
#include "Primitives.h"

class Camera
{
private:
	Vector3f pos;
	Vector3f target;
	Vector3f up;
	float fov;
	float width;
	float height;
	float znear;
	float zfar;
	float angleH;
	float angleV;
	Matrix4f projectionM;
	Matrix4f translationM;
	Matrix4f rotationM;
	Matrix4f cameraM;
	bool isOrthogonal;
public:
	Camera();
	Camera(float _width, float _height);
	Camera(float _width, float _height, float _fov, float _znear, float _zfar, Vector3f _pos, Vector3f _target, Vector3f _up);
	void calcMatrix();
	void calcAngles();
	Matrix4f& getCameraMatrix();
	float getWidth();
	float getHeight();
	Vector3f& getPosition();
	Vector3f& getTarget();
	Vector3f& getUp();
	void resize(int width, int height);
	void translate(float _x, float _y, float _z);
	void setPosition(float _x, float _y, float _z);
	void setTarget(float _x, float _y, float _z);
	void rotate(float h, float v);
	float getAngleH();
	float getAngleV();
	float getRatio();
	void MakeOrthogonal(float scale);
};