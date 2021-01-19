#include "GeometryLoader.h"

#include "05_ECS/Component.h"

void GeometryLoader::loadGeometry(ComponentGeometry* geometry, std::vector<float> &vertices, std::vector<unsigned int> &indices){
	Geometry2D* geom = geometries[geometry->getType()];

	geom->getVertices(vertices,geometry->getNumPoints(),geometry->getAngle(),geometry->getInnerRadius());
	geom->getIndices(indices, geometry->getNumPoints(), geometry->getAngle(),geometry->getInnerRadius());
}

void GeometryLoader::registerGeometry(GeometryType type, Geometry2D* geometry){
	geometries[type] = geometry;
}