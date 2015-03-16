#ifndef __IX_SHADERS__
#define __IX_SHADERS__
#pragma once

#include <string>

std::string default_vert = "#version 120\n"
							"attribute vec3 v_position;"
							"attribute vec2 v_texcoord;"
							"varying vec2 texcoord;"
							"uniform mat4 model;"
							"uniform mat4 proj;"
							"uniform vec4 cliprect;"
							"void main()"
							"{"
							"	gl_Position = proj * model * vec4(v_position, 1.0);"

							"	texcoord.x = (cliprect.x + v_texcoord.x) * cliprect.z;"
							"	texcoord.y = (cliprect.y + v_texcoord.y) * cliprect.w;"
							"}";

std::string default_frag = "#version 120\n"
							"uniform sampler2D image;"
							"varying vec2 texcoord;"
							"void main()"
							"{"
							"	gl_FragColor = texture2D(image, texcoord);"
							"}";

#endif //__IX_SHADERS__