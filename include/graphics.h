#ifndef __IX_GRAPHICS__
#define __IX_GRAPHICS__

#define GL_ES

#define GLEW_STATIC
#include <GL/glew.h>

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#define GLM_FORCE_PURE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <cstdlib>

#define SAFE_DELETE(x) { if(x) delete x; x = NULL; }

#endif //__IX_GRAPHICS__
