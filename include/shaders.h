#ifndef __IX_SHADERS__
#define __IX_SHADERS__
#pragma once

#define _ST(x) #x

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
                                     uniform vec3 u_lightFalloff;
                                     uniform vec4 u_ambientColor;
                                     uniform float u_lightIntens;
                                     uniform float m_specularPower;
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

                                         // Get the distance
                                         float D = length(vertPos - lightPos);

                                         float intensity = 1.0 / ( u_lightFalloff.x + (u_lightFalloff.y*D) + (u_lightFalloff.z*D*D));

                                         vec3 N = normalize((2.0 * (normal_tex.xyz * normal_tex.w)) - 1.0);
                                         N *= m_normalPower;
                                         vec3 L = normalize(lightPos - vertPos);

                                         float diffusePower = max(dot(N, L), 0.0);
                                         vec3 diffuseComponent = diffusePower * m_diffuseColor.rgb * u_lightIntens;

                                         vec3 R = reflect(-L, N);
                                         float specularPower = 0.0;

                                         if (diffusePower > 0.0) {
                                             float StoC = max(dot(vec3(0.0, 0.0, 1.0), R), 0.0);
                                             specularPower = pow(StoC, m_specularPower);
                                         }
                                         vec3 specularComponent = specularPower * m_specularColor.rgb * u_lightIntens;

                                         vec3 linearColor = u_ambientColor.rgb + intensity * (diffuseComponent + specularComponent);
                                         vec3 finalColor = u_lightColor.rgb * color_tex.rgb * linearColor;

                                         gl_FragColor = vec4(finalColor, color_tex.a);
                                     } );

#endif //__IX_SHADERS__
