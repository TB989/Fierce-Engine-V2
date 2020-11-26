#include "Transform.h"

Transform2D::Transform2D(float x, float y, float scaleX, float scaleY, float rotation) {
	position = new Vector2f(x, y);
	scale = new Vector2f(scaleX, scaleY);
	m_rotation = rotation;
}