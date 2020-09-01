#pragma once

#include "Common.h"
#include <exception>

class Fierce_Exception :public std::runtime_error {
public:
	Fierce_Exception(std::string message) :runtime_error(message) {}
};