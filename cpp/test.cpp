/*
 * test.cpp
 *
 *  Created on: Oct 13, 2021
 *      Author: KZ
 */

#include "doctest.h"

#include <string>

TEST_CASE("Hello World") {
	std::string hello = "Hello";
	std::string world = "World";
	std::string result = hello + " " + world;
	CHECK(result == "Hello World");
}
