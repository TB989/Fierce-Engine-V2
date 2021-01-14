#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "06_Geometry/Geometry2D.h"

/* SystemIncludes*/
#include <vector>
#include <map>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/
class ComponentGeometry;

class GeometryLoader{
public:
	void loadGeometry(ComponentGeometry* geometry,std::vector<float> &vertices,std::vector<unsigned int> &indices);
	void registerGeometry(GeometryType type, Geometry2D* geometry);
private:
	std::map<GeometryType, Geometry2D*> geometries;
};