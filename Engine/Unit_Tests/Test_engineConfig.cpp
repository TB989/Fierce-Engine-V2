#include "UnitTests.h"
#include "core/EngineSettings.h"
#include "parser/Parser.h"

Test_engineConfig::Test_engineConfig() {
	eventSystem->addListener(this, &Test_engineConfig::onAppInit);
}

void Test_engineConfig::onAppInit(AppInitEvent* event) {
	std::map<std::string, std::string> settings = Parser::parsePropertiesFile("C:/Users/Tobias/Desktop/GameEngine/Engine/Engine.ini");

	std::map<std::string, std::string>::iterator it = settings.begin();
	while (it != settings.end()) {
		std::string key = it->first;
		std::string value = it->second;
		Loggers::CORE->info("Key: %s, Value: %s",key.c_str(),value.c_str());
		it++;
	}

	m_settings.parse(settings);
}