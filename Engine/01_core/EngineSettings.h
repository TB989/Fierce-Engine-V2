#pragma once

/* Includes:
*  -Parent class
*  -Objects: Object myObject;
*/
#include "99_utils/FierceStrings.h"

/* SystemIncludes*/
#include <map>

/* Forward declarations: 
*  -Pointers:  Pointer* myPointer;
*              Reference& myReference;
*  -Functions: Object MyFunction(Object myObject);
*              Pointer* MyFunction(Pointer* myPointer);
*              Reference& MyFunction(Reference& myReference);
*/

enum API {
	UNKNOWN,
	VULKAN,
	OPEN_GL,
	DIRECT_X
};

struct EngineSettings {
	//Window
	bool fullscreen = false;
	int width = 800;
	int height = 600;

	//Graphics API
	API api = VULKAN;
	int apiVersionMajor = 1;
	int apiVersionMinor = 0;
	int apiVersionPatch = 0;

	void parse(std::map<std::string, std::string> settings) {
		std::map<std::string, std::string>::iterator it = settings.begin();
		while (it != settings.end()) {
			std::string key = it->first;
			std::string value = it->second;
			if (key == "fullscreen" || key == "FULLSCREEN") {
				if (value == "true" || value == "TRUE") {
					fullscreen = true;
				}
				if (value == "false" || value == "FALSE") {
					fullscreen = false;
				}
			}
			if (key == "width" || key == "WIDTH") {
				width = std::stoi(value);
			}
			if (key == "height" || key == "HEIGHT") {
				height = std::stoi(value);
			}
			if (key == "api" || key == "API") {
				if (value == "vulkan" || value == "VULKAN" || value == "vk" || value == "VK") {
					api = VULKAN;
				}
				else if (value == "opengl" || value == "OPENGL" || value == "gl" || value == "GL") {
					api = OPEN_GL;
				}
				else if (value == "directx" || value == "DIRECTX" || value == "dx" || value == "DX") {
					api = DIRECT_X;
				}
				else {
					api = UNKNOWN;
				}
			}
			if (key == "version" || key == "VERSION") {
				std::vector<std::string> temp = split(value, '.');
				switch (temp.size()) {
				case 0:
					apiVersionMajor = 0;
					apiVersionMinor = 0;
					apiVersionPatch = 0;
					break;
				case 1:
					apiVersionMajor = std::stoi(temp[0]);
					apiVersionMinor = 0;
					apiVersionPatch = 0;
					break;
				case 2:
					apiVersionMajor = std::stoi(temp[0]);
					apiVersionMinor = std::stoi(temp[1]);
					apiVersionPatch = 0;
					break;
				default:
					apiVersionMajor = std::stoi(temp[0]);
					apiVersionMinor = std::stoi(temp[1]);
					apiVersionPatch = std::stoi(temp[2]);
					break;
				}
			}
			it++;
		}
	}
};