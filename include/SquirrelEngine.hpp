#ifndef __SQUIRREL_ENGINE_DQBIX__
#define __SQUIRREL_ENGINE_DQBIX__
#pragma once
#include <vector>
#include <iostream>
#include <cstdarg>

#include "squirrel.hpp"

class SquirrelEngine
{
public:
	SquirrelEngine()
	{ 
		S = SQBound::Create(1024, true, SquirrelEngine::printfunc, SquirrelEngine::printfunc);
	}

	~SquirrelEngine()
	{
		SQBound::Destroy(S);
	}

	HSQUIRRELVM getSVM() const { return S; }

	void RunScript(const char* filename);

	inline static void printfunc(HSQUIRRELVM v, const SQChar* s, ...)
	{
		const size_t cSize = strlen(s) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, s, cSize);

		va_list arglist;
		va_start(arglist, s);
		vwprintf(wc, arglist);
		va_end(arglist);
	}

	inline static void printString(std::wstring str)
	{
		wprintf(str.c_str());
		std::cout << std::endl;
	}
private:
	HSQUIRRELVM S;
};


#endif //__SQUIRREL_ENGINE_DQBIX__