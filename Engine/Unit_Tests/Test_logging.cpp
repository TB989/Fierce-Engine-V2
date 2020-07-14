#include "UnitTests.h"

void Test_logging::init(){
	Loggers::CORE->error("ERROR %i", 102);
	Loggers::CORE->warn("WARN %1.5f", 85.255496464);
	Loggers::CORE->info("INFO %s", "String");
}

void Test_logging::update(){
	
}

void Test_logging::render(){

}

void Test_logging::cleanUp(){
	
}