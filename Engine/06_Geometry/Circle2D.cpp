#include "Geometry2D.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Circle2D::getVertices(std::vector<float>& vertices,int numPoints,float radius,float angle) {
	vertices.push_back(0);
	vertices.push_back(0);

	float da = angle / (float)numPoints;
	for (int i = 0;i<numPoints;i++) {
		float x = 0.5*sin(M_PI / 180.0f * i * da)+0.5;
		float y = 0.5*cos(M_PI / 180.0f * i * da)+0.5;
		vertices.push_back(radius*x);
		vertices.push_back(radius*y);
	}
}

void Circle2D::getIndices(std::vector<int>& indices, int numPoints, float radius, float angle) {
	for (int i = 0; i < numPoints-1; i++) {
		indices.push_back(0);
		indices.push_back(i+1);
		indices.push_back(i+2);
	}

	if (angle==360) {
		indices.push_back(0);
		indices.push_back(numPoints);
		indices.push_back(1);
	}
}