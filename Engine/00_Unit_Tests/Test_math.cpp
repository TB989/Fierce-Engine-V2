#include "UnitTests.h"

#include "02_system/01_logging/Logger.h"
#include "02_system/02_event/EventSystem.h"
#include "04_math/01_vector/Vector.h"
#include "04_math/02_matrix/Matrix.h"

Test_math::Test_math() {
	m_settings.windowMode = HEADLESS;
	eventSystem->addListener(this, &Test_math::onAppInit);
}

void Test_math::onAppInit(AppInitEvent* event) {
	float numbers1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	float numbers2[] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };

	Mat4 m1(numbers1);
	Mat4 m2(numbers2);
	Mat4 m3;
	Mat4 m4;

	m3=m2*m2;

	m3.print("M3");

	bool test = m3 != m2;

	Vector3f v1(1,2,3);
	Vector3f v2(5,9,3);

	Vector3f v3 = Vector3f::cross(v1, v2);

	v3.print("V3");
}