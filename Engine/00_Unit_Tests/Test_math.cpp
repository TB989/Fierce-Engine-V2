#include "UnitTests.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"
#include "04_math/01_vector/Vector.h"

Test_math::Test_math() {
	eventSystem->addListener(this, &Test_math::onAppInit);
}

void Test_math::onAppInit(AppInitEvent* event) {
	Vector3f v1(1,2,1);
	Vector3f v2(2,4,1);
	Vector3f v3 = Vector3f::cross(v1, v2);

	v3.print();
}