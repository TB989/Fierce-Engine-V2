#include "UnitTests.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"

#include "05_ECS/EntityManager.h"
#include "05_ECS/ComponentManager.h"
#include "05_ECS/Example_Components.h"

Test_ECS::Test_ECS() {
	m_settings.windowMode = HEADLESS;
	eventSystem->addListener(this, &Test_ECS::onAppInit);
}

void Test_ECS::onAppInit(AppInitEvent* event) {
	EntityManager* manager = new EntityManager(3);
	ComponentManager* comps=new ComponentManager();

	comps->registerComponent<Name>(3);

	Entity entity1 = manager->createEntity();
	Entity entity2 = manager->createEntity();
	Entity entity3 = manager->createEntity();

	comps->addComponent(entity1, Name{"Entity1"});
	comps->addComponent(entity2, Name{ "Entity2" });
	comps->addComponent(entity3, Name{ "Entity3" });

	Name name = comps->getComponent<Name>(entity1);

	Loggers::ECS->info("Name: %s",name.name);

	comps->removeComponent<Name>(entity1);
	comps->removeComponent<Name>(entity2);
	comps->removeComponent<Name>(entity3);

	manager->destroyEntity(entity1);
	manager->destroyEntity(entity2);
	manager->destroyEntity(entity3);

	comps->unregisterComponent<Name>();

	delete comps;
	delete manager;
}