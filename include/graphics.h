#ifndef __IX_GRAPHICS__
#define __IX_GRAPHICS__

#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>

#define GLM_FORCE_PURE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#define SAFE_DELETE(x) { if(x) delete x; x = nullptr; }
#endif //__IX_GRAPHICS__