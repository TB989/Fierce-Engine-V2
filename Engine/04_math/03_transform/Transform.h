#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

#include "04_math/01_vector/Vector.h"

class Transform {

};

class Transform2D : Transform {
private:
	Vector2f* position;
	Vector2f* scale;
	float m_rotation;
public:
	Transform2D(float x, float y, float scaleX, float scaleY, float rotation);
};

class Transform3D : Transform {
private:
	Vector3f* position;
	Vector3f* scale;
	Vector3f* rotation;
};