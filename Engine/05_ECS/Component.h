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

enum ComponentType {
	MESH,
	GEOMETRY,
	MATERIAL_COLOR
};

class Component{
public:
	virtual ComponentType getComponentType() = 0;
};

class ComponentMesh : public Component {
public:
	ComponentMesh(GL_VAO* vao) {
		m_vao = vao;
	}

	ComponentType getComponentType() { return ComponentType::MESH; }

	void render() {
		m_vao->bind();
		m_vao->draw();
		m_vao->unbind();
	}
private:
	GL_VAO* m_vao;
};

class ComponentGeometry :public Component {
public:
	ComponentGeometry(GeometryType type,int numPoints,float angle,float innerRadius) {
		m_type = type;
		m_numPoints = numPoints;
		m_angle = angle;
		m_innerRadius = innerRadius;
	}

	ComponentType getComponentType() { return ComponentType::GEOMETRY; }

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

class ComponentMaterialColor :public Component {
public:
	ComponentMaterialColor(float r,float g,float b) {
		m_r = r;
		m_g = g;
		m_b = b;
	}

	ComponentType getComponentType() { return ComponentType::MATERIAL_COLOR; }

	float getR() { return m_r; }
	float getG() { return m_g; }
	float getB() { return m_b; }
private:
	float m_r;
	float m_g;
	float m_b;
};