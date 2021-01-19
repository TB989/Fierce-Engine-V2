#include "Geometry2D.h"

void Triangle2D::getVertices(std::vector<float>& vertices, int numPoints, float angle, float innerRadius) {
	vertices.push_back(0);
	vertices.push_back(0);

	vertices.push_back(0.5f);
	vertices.push_back(1);

	vertices.push_back(1);
	vertices.push_back(0);
}

void Triangle2D::getIndices(std::vector<unsigned int>& indices, int numPoints, float angle, float innerRadius) {
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
}