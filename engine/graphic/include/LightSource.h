#pragma once
#include <GL/glew.h>
#include "Primitives.h"
#include "Shader.h"
#include <vector>

class LightSource
{
private:
	Vector3f col;
	bool shadows;
public:
	LightSource();
	LightSource(Vector3f _col);
	void SetColor(Vector3f _col);
	void SetColor(float r, float g, float b);
	Vector3f GetColor();
	void SetShadows(bool state);
	bool GetShadows();
};

class OmniLight : public LightSource
{
private:
	Vector3f pos;
public:
	OmniLight();
	OmniLight(Vector3f _col);
	OmniLight(Vector3f _col, Vector3f _pos);
	void SetPosition(Vector3f _pos);
	void SetPosition(float x, float y, float z);
	Vector3f GetPosition();
};

class DirectLight : public LightSource
{
private:
	Vector3f dir;
public:
	DirectLight();
	DirectLight(Vector3f _col);
	DirectLight(Vector3f _col, Vector3f _dir);
	void SetDirection(Vector3f _dir);
	void SetDirection(float x, float y, float z);
	Vector3f GetDirection();
};
