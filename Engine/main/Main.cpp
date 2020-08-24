#include "Unit_Tests/UnitTests.h"

int main() {
	Test_logging app;

	try {
		app.run();
	}
	catch (const std::runtime_error& e) {
		Loggers::CORE->error(e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}