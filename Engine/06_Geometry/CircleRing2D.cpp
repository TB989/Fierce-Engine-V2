#include "Geometry2D.h"

void CircleRing2D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius) {
	addCircleVertices2D(vertices, 0.5f, 0.5f, numPoints, innerRadius, angle);
	addCircleVertices2D(vertices, 0.5f, 0.5f, numPoints, 0.5f, angle);
}

void CircleRing2D::getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius) {
	addCircleRingIndices(indices,numPoints,angle,0,numPoints);
}