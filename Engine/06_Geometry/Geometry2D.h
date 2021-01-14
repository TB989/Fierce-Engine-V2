#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

/* SystemIncludes*/
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

enum GeometryType {
	RECTANGLE,
	CIRCLE,
	CICLE_RING,
	TRIANGLE
};

class Geometry2D{
public:
	virtual void getVertices(std::vector<float>& vertices, int numPoints, float angle) = 0;
	virtual void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle) = 0;
};

class Rectangle2D :public Geometry2D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle);
};

class Circle2D :public Geometry2D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle);
};