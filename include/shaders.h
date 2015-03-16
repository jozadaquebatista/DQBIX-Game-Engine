#ifndef __IX_SHADERS__
#define __IX_SHADERS__
#pragma once

#include <string>
const std::string text_vert = "#version 120\n"
"attribute vec2 position;"
"attribute vec2 coord;"
"varying vec2 texcoord;"
"uniform mat4 model;"
"uniform mat4 proj;"
"void main()"
"{"
"	gl_Position = proj * model * vec4(position, 0.0, 1.0);"
"	texcoord = coord;"
"}";

const std::string text_frag = "#version 120\n"
"varying vec2 texcoord;"
"uniform sampler2D image;"
"uniform vec4 color;"
"void main()"
"{"
"	vec4 tex = texture2D(image, texcoord);"
" // libdrawtext generates a black font. So we need to invert it in order to tint it\n"
"	vec4 inv = vec4(1.0-tex.rgb, tex.a);"
"	gl_FragColor = color * inv;"
"}";

const std::string default_vert = "#version 120\n"
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

const std::string default_frag = "#version 120\n"
							"uniform sampler2D image;"
							"varying vec2 texcoord;"
							"void main()"
							"{"
							"	gl_FragColor = texture2D(image, texcoord);"
							"}";

#endif //__IX_SHADERS__