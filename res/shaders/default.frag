#version 120
uniform sampler2D image;

varying vec2 texcoord;

void main()
{
	gl_FragColor = texture2D(image, texcoord);
}