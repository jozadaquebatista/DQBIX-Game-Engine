#include "../include/SquirrelEngine.hpp"

void SquirrelEngine::RunScript(const char* filename)
{
	if (SQBound::DoFile(S, std::string(filename), false))
	{ }
}