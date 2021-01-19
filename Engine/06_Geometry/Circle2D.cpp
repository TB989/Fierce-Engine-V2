#include "Geometry2D.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Circle2D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius) {

	float da = 0;
	if (angle == 360.0f) {
		da = angle / numPoints;
	}
	else {
		da = angle / (numPoints-1);
	}

	vertices.push_back(0.5f);
	vertices.push_back(0.5f);

	for (int i = 0;i<numPoints;i++) {
		vertices.push_back(0.5f+0.5f*sin(M_PI / 180.0f * i*da));
		vertices.push_back(0.5f+0.5f*cos(M_PI / 180.0f * i*da));
	}
}

void Circle2D::getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius) {
	for (int i = 0; i < numPoints-1; i++) {

		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	if (angle == 360.0f) {

		indices.push_back(0);
		indices.push_back(numPoints);
		indices.push_back(1);
	}
}