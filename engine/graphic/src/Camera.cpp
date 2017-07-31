#include "Camera.h"

Camera::Camera() : width(800), height(600), fov(90), znear(0.001f), zfar(1000), pos(Vector3f(0,0,1)),
target(Vector3f(0,0,1)), up(Vector3f(0,1,0)), isOrthogonal(false)
{
	calcAngles();

	projectionM.InitPersProjTransform(fov, width, height, znear, zfar);
	translationM.InitTranslationTransform(-pos.x, -pos.y, -pos.z);
	rotate(0, 0);
}

Camera::Camera(float _width, float _height) : width(_width), height(_height), fov(90), znear(0.001f), zfar(1000),
pos(Vector3f(0, 0, 1)), target(Vector3f(0, 0, 1)), up(Vector3f(0, 1, 0)), isOrthogonal(false)
{
	calcAngles();

	projectionM.InitPersProjTransform(fov, width, height, znear, zfar);
	translationM.InitTranslationTransform(-pos.x, -pos.y, -pos.z);
	rotate(0, 0);
}

Camera::Camera(float _width, float _height, float _fov, float _znear, float _zfar, Vector3f _pos, Vector3f _target, Vector3f _up) :
	width(_width), height(_height), fov(_fov), znear(_znear), zfar(_zfar), pos(_pos), target(_target), up(_up), isOrthogonal(false)
{
	calcAngles();

	projectionM.InitPersProjTransform(fov, width, height, znear, zfar);
	translationM.InitTranslationTransform(-pos.x, -pos.y, -pos.z);
	rotate(0, 0);
}

void Camera::calcMatrix()
{
	Matrix4f m;
	if (isOrthogonal)
	{
		m.InitScaleTransform(1/fov, 1 / fov, 1 / fov);
	}	
	cameraM = m * projectionM * rotationM * translationM;
}

void Camera::calcAngles()
{
	Vector3f HTarget(target.x, 0.0, target.z);
	HTarget.Normalize();
	if (HTarget.z >= 0.0f)
	{
		if (HTarget.x >= 0.0f)
		{
			angleH = 2*M_PI - asin(HTarget.z);
		}
		else
		{
			angleH = M_PI + asin(HTarget.z);
		}
	}
	else
	{
		if (HTarget.x >= 0.0f)
		{
			angleH = asin(-HTarget.z);
		}
		else
		{
			angleH = M_PI -asin(-HTarget.z);
		}
	}
	angleV = -asin(target.Normalize().y) - M_PI / 2;
}

Matrix4f& Camera::getCameraMatrix() 
{
	return cameraM;
}

float Camera::getWidth()
{
	return width;
}

float Camera::getHeight()
{
	return height;
}

Vector3f& Camera::getPosition()
{
	return pos;
}

Vector3f& Camera::getTarget()
{
	return target;
}

Vector3f& Camera::getUp()
{
	return up;
}

void Camera::resize(int _width, int _height)
{
	width = _width;
	height = _height;
}

void Camera::translate(float _x, float _y, float _z)
{
	pos.x += _x;
	pos.y += _y;
	pos.z += _z;
	translationM.InitTranslationTransform(-pos.x, -pos.y, -pos.z);
	calcMatrix();
}

void Camera::setPosition(float _x, float _y, float _z)
{
	pos.x = _x;
	pos.y = _y;
	pos.z = _z;
	translationM.InitTranslationTransform(-pos.x, -pos.y, -pos.z);
	calcMatrix();
}

void Camera::setTarget(float _x, float _y, float _z)
{
	target.x = _x;
	target.y = _y;
	target.z = _z;
	calcAngles();
	rotate(0, 0);
}

void Camera::rotate(float h, float v)
{
	angleH -= h;
	angleV -= v;
	if (angleV > -M_PI*0.01f && !isOrthogonal) angleV = -M_PI*0.01f;
	if (angleV < -M_PI*0.99f && !isOrthogonal) angleV = -M_PI*0.99f;
	target.x = sinf(angleV) * cosf(angleH);
	target.y = cosf(angleV);
	target.z = sinf(angleV) * sinf(angleH);

	up.x = sinf(M_PI / 2 + angleV) * cosf(angleH);
	up.y = cosf(M_PI / 2 + angleV);
	up.z = sinf(M_PI / 2 + angleV) * sinf(angleH);

	rotationM.InitCameraTransform(target, up);
	calcMatrix();
}

float Camera::getAngleH()
{
	return angleH;
}
float Camera::getAngleV()
{
	return angleV;
}

float Camera::getRatio()
{
	return width / height;
}

void Camera::MakeOrthogonal(float scale)
{
	isOrthogonal = true;
	zfar = 2.0f;
	fov = scale;
	projectionM.InitOrthoProjTransform(width, height, znear, zfar);
	angleH = -angleH + M_PI;
	angleV = -angleV;
	rotate(0, 0);
}
