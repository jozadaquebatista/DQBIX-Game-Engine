#ifndef __IX_SHADERS__
#define __IX_SHADERS__
#pragma once

#define _ST(x) #x

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

const std::string default_vert = _ST( #version 120\n
                                     attribute vec3 v_position;
                                     attribute vec2 v_texcoord;
                                     varying vec2 texcoord;
                                     varying vec4 vertex;
                                     uniform mat4 model;
                                     uniform mat4 proj;
                                     uniform vec4 cliprect;
                                     void main()
                                     {
                                        vec4 pos = vec4(v_position, 1.0);
                                        vertex = model * pos;
                                        gl_Position = proj * vertex;
                                        texcoord.x = (cliprect.x + v_texcoord.x) * cliprect.z;
                                        texcoord.y = (cliprect.y + v_texcoord.y) * cliprect.w;
                                     } );

const std::string default_frag = _ST( #version 120\n
                                     uniform sampler2D diffuse;
                                     uniform sampler2D normal;
                                     uniform vec3 u_lightPos;
                                     uniform vec4 u_lightColor;
                                     uniform vec4 u_ambientColor;
                                     uniform float u_lightIntens;
                                     uniform float m_specularPower;
                                     uniform float m_specularHard;
                                     uniform float m_normalPower;
                                     uniform vec4 m_diffuseColor;
                                     uniform vec4 m_specularColor;
                                     varying vec2 texcoord;
                                     varying vec4 vertex;
                                     void main()
                                     {
                                         vec3 lightPos = u_lightPos;
                                         vec3 vertPos = vertex.xyz;

                                         vec4 color_tex = texture2D(diffuse, texcoord);
                                         vec4 normal_tex = texture2D(normal, texcoord);

                                         vec3 n = normal_tex.xyz * 2.0 - vec3(1.0, 1.0, 1.0);
                                         n *= m_normalPower;

                                         float distance = distance(vertPos, lightPos);
                                         vec3 lightDirection = normalize(lightPos - vertPos);

                                         float f = clamp(dot(n, lightDirection), 0.0, 1.0);

                                         vec3 r = reflect(-lightDirection, n);
                                         float fcos = clamp(dot(vec3(0.0, 0.0, 1.0), r), 0.0, 1.0);

                                         vec4 ambient = u_ambientColor;
                                         vec4 diffuse = m_diffuseColor * u_lightColor * f * u_lightIntens / distance / distance;
                                         vec4 specular = m_specularColor * pow(fcos, 32.0) / (m_specularHard + 0.0001);

                                         gl_FragColor = color_tex * (ambient + diffuse + (m_specularPower * specular));
                                     } );

#endif //__IX_SHADERS__
