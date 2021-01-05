#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/

#include "02_system/04_render/GL/GL_VAO.h"

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