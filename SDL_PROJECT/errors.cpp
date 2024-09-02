#include "errors.h"

extern void fatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Enter a key to exit..." << std::endl;
}