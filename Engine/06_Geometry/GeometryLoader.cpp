#include "GeometryLoader.h"

#include "05_ECS/Component.h"

#include "02_system/01_logging/Logger.h"

void GeometryLoader::loadGeometry(ComponentGeometry* geometry, std::vector<float> &vertices, std::vector<unsigned int> &indices){
	Geometry* geom = geometries[geometry->getType()];

	geom->getVertices(vertices,geometry->getNumPoints(),geometry->getAngle(),geometry->getInnerRadius(),geometry->getNumRings());
	geom->getIndices(indices, geometry->getNumPoints(), geometry->getAngle(),geometry->getInnerRadius(), geometry->getNumRings());
}

void GeometryLoader::registerGeometry(GeometryType type, Geometry* geometry){
	geometries[type] = geometry;
}