#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

#include "06_Geometry/Geometry.h"
#include "04_math/04_color/Color.h"

/* SystemIncludes*/
#include <vector>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class GL_VAO;

enum ComponentType {
	MESH,
	GEOMETRY,
	MATERIAL_COLOR,
	MATERIAL_COLORS
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

	/**void render() {
		m_vao->bind();
		m_vao->draw();
		m_vao->unbind();
	}

	void render(GLsizei first,GLsizei count) {
		m_vao->bind();
		m_vao->draw(first,count);
		m_vao->unbind();
	}*/
private:
	GL_VAO* m_vao;
};

class ComponentGeometry :public Component {
public:
	ComponentGeometry(GeometryType type,int numPoints,float angle,float innerRadius,int numRings) {
		m_type = type;
		m_numPoints = numPoints;
		m_angle = angle;
		m_innerRadius = innerRadius;
		m_numRings = numRings;
	}

	ComponentType getComponentType() { return ComponentType::GEOMETRY; }

	GeometryType getType() { return m_type; }
	int getNumPoints() { return m_numPoints; }
	float getAngle() { return m_angle; }
	float getInnerRadius() { return m_innerRadius; }
	float getNumRings() { return m_numRings; }
private :
	GeometryType m_type;
	int m_numPoints;
	float m_angle;
	float m_innerRadius;
	int m_numRings;
};

class ComponentMaterialColor :public Component {
public:
	ComponentMaterialColor(float r,float g,float b) {
		color = new Color3f(r,g,b);
	}

	ComponentType getComponentType() { return ComponentType::MATERIAL_COLOR; }

	float getR() { return color->getR(); }
	float getG() { return color->getG(); }
	float getB() { return color->getB(); }
private:
	Color3f* color;
};

class ComponentMaterialColors :public Component {
public:
	ComponentMaterialColors(std::vector<Color3f*> colors) {
		m_colors = colors;
	}

	Color3f* getNextColor() {
		counter++;
		counter=counter% m_colors.size();
		return m_colors[counter];
	}

	void reset() {
		counter = -1;
	}

	ComponentType getComponentType() { return ComponentType::MATERIAL_COLORS; }

private:
	std::vector<Color3f*> m_colors;

	int counter = -1;
};