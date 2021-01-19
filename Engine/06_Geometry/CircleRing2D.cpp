#include "Geometry2D.h"

#define _USE_MATH_DEFINES
#include <math.h>

void CircleRing2D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius) {

	float da = 0;
	if (angle == 360.0f) {
		da = angle / numPoints;
	}
	else {
		da = angle / (numPoints - 1);
	}

	//Inner circle
	for (int i = 0; i < numPoints; i++) {
		vertices.push_back(0.5f + innerRadius * sin(M_PI / 180.0f * i * da));
		vertices.push_back(0.5f + innerRadius * cos(M_PI / 180.0f * i * da));
	}

	//Outer circle
	for (int i = 0; i < numPoints; i++) {
		vertices.push_back(0.5f + 0.5f * sin(M_PI / 180.0f * i * da));
		vertices.push_back(0.5f + 0.5f * cos(M_PI / 180.0f * i * da));
	}
}

void CircleRing2D::getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius) {
	for (int i = 0; i < numPoints - 1; i++) {
		//First triangle
		indices.push_back(i);
		indices.push_back(i + numPoints + 1);
		indices.push_back(i + 1);

		//Second triangle
		indices.push_back(i);
		indices.push_back(i + numPoints);
		indices.push_back(i + numPoints + 1);
	}

	if (angle == 360.0f) {
		//First triangle
		indices.push_back(numPoints - 1);
		indices.push_back(numPoints);
		indices.push_back(0);

		//Second triangle
		indices.push_back(numPoints - 1);
		indices.push_back(2 * numPoints - 1);
		indices.push_back(numPoints);
	}
}