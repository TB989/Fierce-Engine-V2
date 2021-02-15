#include "Geometry.h"

void Rectangle2D::getVertices(std::vector<float> &vertices, int numPoints, float angle, float innerRadius){
	addVertex2D(vertices, 0, 0);
	addVertex2D(vertices, 0, 1);
	addVertex2D(vertices, 1, 1);
	addVertex2D(vertices, 1, 0);
}

void Rectangle2D::getIndices(std::vector<unsigned int> &indices, int numPoints, float angle, float innerRadius){
	addQuadIndices(indices, 0, 1, 2, 3,false);
}