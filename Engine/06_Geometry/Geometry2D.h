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
	CIRCLE_RING,
	TRIANGLE
};

class Geometry2D{
public:
	virtual void getVertices(std::vector<float>& vertices, int numPoints, float angle,float innerRadius) = 0;
	virtual void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius) = 0;
protected:
	void addVertex2D(std::vector<float>& vertices, float x, float y);
	void addCircleVertices2D(std::vector<float>& vertices, float x, float y, int numPoints, float radius, float angle);

	void addTriangleIndices(std::vector<unsigned int>& indices, int i1,int i2,int i3);
	void addQuadIndices(std::vector<unsigned int>& indices, int i1, int i2, int i3,int i4);
	void addCircleIndices(std::vector<unsigned int>& indices, int numPoints, float angle, int center, int start);
	void addCircleRingIndices(std::vector<unsigned int>& indices, int numPoints, float angle, int center, int start);
};

class Rectangle2D :public Geometry2D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius);
};

class Circle2D :public Geometry2D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius);
};

class CircleRing2D :public Geometry2D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius);
};

class Triangle2D :public Geometry2D {
public:
	void getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius);
	void getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius);
};