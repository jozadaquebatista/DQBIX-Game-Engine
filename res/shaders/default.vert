#version 120

attribute vec3 v_position;
attribute vec2 v_texcoord;

varying vec2 texcoord;

uniform mat4 model;
uniform mat4 proj;

uniform vec4 cliprect;

void main() 
{
	gl_Position = proj * model * vec4(v_position, 1.0);

	// Animated texCoords =)
	texcoord.x = (cliprect.x + v_texcoord.x) * cliprect.z;
	texcoord.y = (cliprect.y + v_texcoord.y) * cliprect.w;
}