#include "00_Unit_Tests/UnitTests.h"
#include "01_core/errorHandling/Exceptions.h"
#include "02_system/01_logging/Logger.h"

int main() {
	Test_math app;

	try {
		app.run();
	}
	catch (const Fierce_Exception& e) {
		Loggers::CORE->error(e.what());
		return EXIT_FAILURE;
	}
	catch (const GL_Exception& e) {
		Loggers::GL->error(e.what());
		return EXIT_FAILURE;
	}
	catch (const Win_Exception& e) {
		Loggers::CORE->error(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}