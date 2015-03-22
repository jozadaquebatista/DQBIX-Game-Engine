#include "../include/Helpers.hpp"

std::string readFile(std::string filepath)
{
	std::ifstream t(filepath);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	return str;
}
