#pragma once

#include "Common.h"
#include <Windows.h>

enum FIERCE_ERROR {
	FE_NO_ERROR,
	FE_WINDOW_ERROR
};

inline void CHECK_FIERCE(FIERCE_ERROR result, std::string message) {
	std::string errorString;
	switch (result) {
	case FE_NO_ERROR:
		return;
	case FE_WINDOW_ERROR:
		errorString = "FIERCE Error: FE_WINDOW_ERROR";
		break;
	default:
		errorString = "FIERCE Error: FE_UNKNOWN_ERROR";
	}

	std::wstring temp1 = std::wstring(message.begin(), message.end());
	std::wstring temp2 = std::wstring(errorString.begin(), errorString.end());
	MessageBox(NULL, temp1.c_str(), temp2.c_str(), MB_ICONERROR);
	throw Fierce_Exception(message.c_str());
}