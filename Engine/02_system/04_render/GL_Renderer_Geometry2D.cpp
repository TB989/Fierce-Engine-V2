#include "GL_Renderer_Geometry2D.h"

#include "02_system/04_render/GL/GL_Shader.h"
#include "02_system/04_render/GL/GL_Pipeline.h"
#include "02_system/04_render/GL/VertexAttribute.h"

#include "02_system/01_logging/Logger.h"

#include "04_math/04_color/Color.h"

GL_Renderer_Geometry2D::GL_Renderer_Geometry2D() {
	loadShaders();
	createPipeline();
}

void GL_Renderer_Geometry2D::loadShaders() {
	vertexShader = new GL_Shader("Shader_Color2D.vs");
	fragmentShader = new GL_Shader("Shader_Color.fs");
}

void GL_Renderer_Geometry2D::createPipeline() {
	pipeline = new GL_Pipeline("Geometry_2D", vertexShader, fragmentShader);
	pipeline->addVertexAttribute(VertexAttribute::POS2);
	pipeline->addUniformLocation("projectionMatrix");
	pipeline->addUniformLocation("modelMatrix");
	pipeline->addUniformLocation("color");
	pipeline->create();
}

void GL_Renderer_Geometry2D::renderEntity(Entity2D* entity){
	ComponentMaterialColors* colors = (ComponentMaterialColors*)(entity->getComponent(ComponentType::MATERIAL_COLORS));
	colors->reset();
	ComponentMesh* mesh = (ComponentMesh*)(entity->getComponent(ComponentType::MESH));
	Color3f* color;
	ComponentGeometry* geo= (ComponentGeometry*)(entity->getComponent(ComponentType::GEOMETRY));
	int count = 0;

	switch (geo->getType()) {
	case RECTANGLE:
	case TRIANGLE:
		color = colors->getNextColor();
		pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
		mesh->render();
		break;
	case CIRCLE:
		if (geo->getAngle() == 360.0f) {
			count = geo->getNumPoints();
		}
		else {
			count = geo->getNumPoints()-1;
		}

		for (int i = 0;i<count;i++) {
			color = colors->getNextColor();
			pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(i*3,3);
		}
		break;
	case CIRCLE_RING:
		if (geo->getAngle() == 360.0f) {
			count = geo->getNumPoints();
		}
		else {
			count = geo->getNumPoints() - 1;
		}

		for (int i = 0; i < count; i++) {
			color = colors->getNextColor();
			pipeline->loadUniform("color", color->getR(), color->getG(), color->getB());
			mesh->render(i * 6, 6);
		}
		break;
	}
}