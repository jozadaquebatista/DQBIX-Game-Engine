#ifndef __IX_SHADERS__
#define __IX_SHADERS__
#pragma once

#include <string>

const std::string shaded_frag = "#version 120\n"
"uniform sampler2D diffuse;"
"uniform sampler2D normal;"
"uniform vec2 Resolution;"
"uniform vec3 LightPos;"
"uniform vec4 LightColor;"
"uniform vec4 AmbientColor;"
"uniform vec3 Falloff;"
"varying vec2 texcoord;"
"void main()"
"{"
"	vec4 diffuseColor = texture2D(diffuse, texcoord);"
"	vec3 normalMap = texture2D(normal, texcoord).xyz;"
"	vec3 lightDir = vec3(LightPos.xy - (gl_FragCoord.xy / Resolution.xy), LightPos.z);"
"	lightDir.x *= Resolution.x / Resolution.y;"
"	float D = length(lightDir);"
"	vec3 N = normalize(normalMap * 2.0 - 1.0);"
"	vec3 L = normalize(lightDir);"
"	vec3 diffusePremul = (LightColor.rgb * LightColor.a) * max(dot(N, L), 0.0);"
"	vec3 Ambient = AmbientColor.rgb * AmbientColor.a;"
"	float Attenuation = 1.0 / (Falloff.x + (Falloff.y*D) + (Falloff.z*D*D));"
"	vec3 Intensity = Ambient + diffusePremul * Attenuation;"
"	vec3 FinalColor = diffuseColor.rgb * Intensity;"
"	gl_FragColor = vec4(FinalColor, diffuseColor.a);"
"}";

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