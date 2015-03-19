#ifndef __IX_SQUIRREL_BIND__
#define __IX_SQUIRREL_BIND__
#pragma once

#include <SquirrelBound.h>
#include <cstdio>
#include <iostream>

#define SAFE_DELETE(x) { if(x) delete x; x = nullptr; }
#endif //__IX_SQUIRREL_BIND__