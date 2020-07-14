#include "Parser.h"

std::map<std::string, std::string> Parser::parsePropertiesFile(std::string filename) {
	std::string line;
	std::vector<std::string> tokens;
	std::ifstream myfile(filename);
	std::map<std::string, std::string> settings;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			trim(line);

			//Empty line
			if (line.empty()) {
				continue;
			}

			//Comment
			if (startsWith(line, "//")) {
				continue;
			}

			//Invalid line
			if (!contains(line, "=")) {
				continue;
			}

			//Valid line
			else {
				tokens = split(line, '=');
				trim(tokens[0]);
				trim(tokens[1]);
				settings.insert(std::make_pair(tokens[0], tokens[1]));
			}
		}
		myfile.close();
	}
	else {
		throw std::runtime_error("Unable to open \"Engine.ini\".");
	}
	return settings;
}