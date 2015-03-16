#version 120

uniform sampler2D image;
varying vec2 texcoord;
void main()
{
	vec4 color = texture2D(image, texcoord);
	vec4 sum = vec4(0.0);
	
	sum += texture2D(image, texcoord + vec2(0, -0.01));
	sum += texture2D(image, texcoord + vec2(0, 0.01));
	sum += texture2D(image, texcoord + vec2(-0.01, 0));
	sum += texture2D(image, texcoord + vec2(0.01, 0));
		
	gl_FragColor = sum * 0.2 + color;
}