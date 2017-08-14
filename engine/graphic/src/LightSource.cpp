#include "LightSource.h"

//=============LIGTHSOURCE=============

LightSource::LightSource() : col(Vector3f(1.0f, 1.0f, 1.0f)), shadows(false)
{

}

LightSource::LightSource(Vector3f _col) : col(_col), shadows(false)
{

}

void LightSource::SetColor(Vector3f _col)
{
	col = _col;
}

void LightSource::SetColor(float r, float g, float b)
{
	col.x = r;
	col.y = g;
	col.z = b;
}

Vector3f LightSource::GetColor()
{
	return col;
}

void LightSource::SetShadows(bool state)
{
	shadows = state;
}

bool LightSource::GetShadows()
{
	return shadows;
}

//=============OMNILIGHT=============

OmniLight::OmniLight() : LightSource()
{

}

OmniLight::OmniLight(Vector3f _col) : LightSource(_col)
{

}

OmniLight::OmniLight(Vector3f _col, Vector3f _pos) : LightSource(_col), pos(_pos)
{

}

void OmniLight::SetPosition(Vector3f _pos)
{
	pos = _pos;
}

void OmniLight::SetPosition(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

Vector3f OmniLight::GetPosition()
{
	return pos;
}

//=============DIRECTLIGHT=============

DirectLight::DirectLight() : LightSource()
{

}

DirectLight::DirectLight(Vector3f _col) : LightSource(_col)
{

}

DirectLight::DirectLight(Vector3f _col, Vector3f _dir) : LightSource(_col), dir(_dir.Normalize())
{

}

void DirectLight::SetDirection(Vector3f _dir)
{
	dir = _dir.Normalize();
}

void DirectLight::SetDirection(float x, float y, float z)
{
	dir.x = x;
	dir.y = y;
	dir.z = z;
	dir.Normalize();
}

Vector3f DirectLight::GetDirection()
{
	return dir;
}
