#include "UnitTests.h"
#include "core/EngineSettings.h"
#include "parser/Parser.h"

void Test_engineConfig::init() {
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

void Test_engineConfig::update() {

}

void Test_engineConfig::render() {

}

void Test_engineConfig::cleanUp() {

}