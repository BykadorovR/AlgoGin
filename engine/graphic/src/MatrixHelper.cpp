#include "MatrixHelper.h"
#include "GLIncludes.h"
#include "math.h"

void MatrixHelper::setPosition(const Vector3f& position) {
	_position[0][0] = 1.0f; _position[0][1] = 0.0f; _position[0][2] = 0.0f; _position[0][3] = position.x;
	_position[1][0] = 0.0f; _position[1][1] = 1.0f; _position[1][2] = 0.0f; _position[1][3] = position.y;
	_position[2][0] = 0.0f; _position[2][1] = 0.0f; _position[2][2] = 1.0f; _position[2][3] = position.z;
	_position[3][0] = 0.0f; _position[3][1] = 0.0f; _position[3][2] = 0.0f; _position[3][3] = 1.0f;
}

void MatrixHelper::setRotate(const Vector3f& rotate) {
	Matrix4f rx, ry, rz;

	const float x = static_cast<float>(ToRadian(rotate.x));
	const float y = static_cast<float>(ToRadian(rotate.y));
	const float z = static_cast<float>(ToRadian(rotate.z));

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

	_rotate = rz * ry * rx;
}

void MatrixHelper::setScale(const Vector3f& scale) {
	_scale[0][0] = scale.x; _scale[0][1] = 0.0f; _scale[0][2] = 0.0f; _scale[0][3] = 0.0f;
	_scale[1][0] = 0.0f; _scale[1][1] = scale.y; _scale[1][2] = 0.0f; _scale[1][3] = 0.0f;
	_scale[2][0] = 0.0f; _scale[2][1] = 0.0f; _scale[2][2] = scale.z; _scale[2][3] = 0.0f;
	_scale[3][0] = 0.0f; _scale[3][1] = 0.0f; _scale[3][2] = 0.0f; _scale[3][3] = 1.0f;
}

Matrix4f& MatrixHelper::getMatrix() {
	_matrix = _position * _rotate * _scale;
	return _matrix;
}
