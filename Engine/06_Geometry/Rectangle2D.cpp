#include "Geometry2D.h"

void Rectangle2D::getVertices(std::vector<float> &vertices, int numPoints, float angle){
	vertices.push_back(0);
	vertices.push_back(0);

	vertices.push_back(0);
	vertices.push_back(1);

	vertices.push_back(1);
	vertices.push_back(1);

	vertices.push_back(1);
	vertices.push_back(0);
}

void Rectangle2D::getIndices(std::vector<unsigned int> &indices, int numPoints, float angle){
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);
}