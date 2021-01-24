#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "99_utils/FierceStrings.h"
#include "05_ECS/Component.h"

/* SystemIncludes*/
#include <typeinfo>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

class Transform2D;
class Transform3D;

class Entity {
public:
	Entity(std::string name) { m_name = name; }

	void addComponent(Component* component) { components.push_back(component); }
	Component* getComponent(ComponentType type) {
		for (Component* component:components) {
			if (component->getComponentType()==type) {
				return component;
			}
		}
		return nullptr;
	}
protected:
	std::string m_name;
	std::vector<Component*> components;
};

class Entity2D : public Entity{
public:
	Entity2D(std::string name) :Entity(name) {};

	void setTransform(Transform2D* transform) { m_transform = transform; }
	Transform2D* getTransform() { return m_transform; }

private:
	Transform2D* m_transform = nullptr;
};

class Entity3D : public Entity{
	Entity3D(std::string name) :Entity(name) {};

	void setTransform(Transform3D* transform) { m_transform = transform; }
	Transform3D* getTransform() { return m_transform; }

private:
	Transform3D* m_transform = nullptr;
};