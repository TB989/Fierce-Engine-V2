#include "Unit_Tests/UnitTests.h"
#include "exceptions/Exceptions.h"

int main() {
	Test_openGLContext app;

	try {
		app.run();
	}
	catch (const Fierce_Exception e) {
		Loggers::CORE->error(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}