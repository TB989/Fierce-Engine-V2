#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

#include "02_system/04_render/GL/GL_VAO.h"
#include "06_Geometry/Geometry2D.h"

/* SystemIncludes*/

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Component{};

class ComponentMesh : public Component {
private:
	GL_VAO* m_vao;
public:
	ComponentMesh(GL_VAO* vao) {
		m_vao = vao;
	}

	void render() {
		m_vao->bind();
		m_vao->draw();
		m_vao->unbind();
	}
};

class ComponentGeometry :public Component {
public:
	ComponentGeometry(GeometryType type,int numPoints,float angle,float innerRadius) {
		m_type = type;
		m_numPoints = numPoints;
		m_angle = angle;
		m_innerRadius = innerRadius;
	}

	GeometryType getType() { return m_type; }
	int getNumPoints() { return m_numPoints; }
	float getAngle() { return m_angle; }
	float getInnerRadius() { return m_innerRadius; }
private :
	GeometryType m_type;
	int m_numPoints;
	float m_angle;
	float m_innerRadius;
};