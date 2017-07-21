#pragma once
#include "Primitives.h"

class Camera
{
private:
	Vector3f pos;
	Vector3f target;
	Vector3f up;
	Vector2f mousePos;
	float fov;
	float width;
	float height;
	float znear;
	float zfar;
	float angleH;
	float angleV;
	Matrix4f perspectiveM;
	Matrix4f translationM;
	Matrix4f rotationM;
	Matrix4f cameraM;
	void calcMatrix();
	void calcAngles();
public:
	Camera();
	Camera(float _width, float _height, float _fov, float _znear, float _zfar, Vector3f _pos, Vector3f _target, Vector3f _up);
	void OnMouse(int x, int y);
	Matrix4f& getCameraMatrix();
	float getWidth();
	float getHeight();
	Vector3f& getPosition();
	Vector3f& getTarget();
	Vector3f& getUp();
	void translate(float _x, float _y, float _z);
	void setPosition(float _x, float _y, float _z);
};