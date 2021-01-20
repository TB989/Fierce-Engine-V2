#include "Geometry2D.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Geometry2D::addVertex2D(std::vector<float>& vertices,float x,float y){
	vertices.push_back(x);
	vertices.push_back(y);
}

void Geometry2D::addCircleVertices2D(std::vector<float>& vertices, float x, float y,int numPoints,float radius,float angle){
	float da = 0;
	if (angle == 360.0f) {
		da = angle / numPoints;
	}
	else {
		da = angle / (numPoints - 1);
	}

	for (int i = 0; i < numPoints; i++) {
		vertices.push_back(x + radius * sin(M_PI / 180.0f * i * da));
		vertices.push_back(y + radius * cos(M_PI / 180.0f * i * da));
	}
}

void Geometry2D::addTriangleIndices(std::vector<unsigned int>& indices, int i1, int i2, int i3){
	indices.push_back(i1);
	indices.push_back(i2);
	indices.push_back(i3);
}

void Geometry2D::addQuadIndices(std::vector<unsigned int>& indices, int i1, int i2, int i3, int i4){
	indices.push_back(i1);
	indices.push_back(i2);
	indices.push_back(i3);

	indices.push_back(i1);
	indices.push_back(i3);
	indices.push_back(i4);
}

void Geometry2D::addCircleIndices(std::vector<unsigned int>& indices,int numPoints,float angle,int center,int start){
	for (int i = 0; i < numPoints - 1; i++) {

		indices.push_back(center);
		indices.push_back(i + start);
		indices.push_back(i + start + 1);
	}

	if (angle == 360.0f) {

		indices.push_back(center);
		indices.push_back(start + numPoints - 1);
		indices.push_back(start);
	}
}

void Geometry2D::addCircleRingIndices(std::vector<unsigned int>& indices, int numPoints, float angle, int start1, int start2){
	for (int i = 0; i < numPoints - 1; i++) {
		//First triangle
		indices.push_back(start1 + i);
		indices.push_back(start2 + i + 1);
		indices.push_back(start1 + i + 1);

		//Second triangle
		indices.push_back(start1 + i);
		indices.push_back(start2 + i);
		indices.push_back(start2 + i + 1);
	}

	if (angle == 360.0f) {
		//First triangle
		indices.push_back(start1 + numPoints - 1);
		indices.push_back(start2);
		indices.push_back(start1);

		//Second triangle
		indices.push_back(start1 + numPoints - 1);
		indices.push_back(start2 + numPoints - 1);
		indices.push_back(start2);
	}
}