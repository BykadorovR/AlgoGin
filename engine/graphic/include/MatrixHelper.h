#include "GLIncludes.h"
#include "Primitives.h"

class MatrixHelper {
private:
	Matrix4f _matrix;
	Matrix4f _position;
	Matrix4f _rotate;
	Matrix4f _scale;

public:
	void setRotate(Vector3f& rotate);
	void setScale(Vector3f& scale);
	void setPosition(Vector3f& position);
	Matrix4f& getMatrix();
};