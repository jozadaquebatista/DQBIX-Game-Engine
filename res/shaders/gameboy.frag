#version 120
uniform sampler2D image;
varying vec2 texcoord;

void main(void)
{
    vec4 color = texture2D(image, texcoord);

    float lum = max(max(color.r, color.g), color.b);

    if (lum > .75)
        color = vec4(0.816, 0.9909, 0.0675, color.a);
    else if (lum > .5)
        color = vec4(0.542, 0.671, 0.05, color.a);
    else if (lum > .25)
        color = vec4(0.187, 0.382, 0.187, color.a);
    else
        color = vec4(0.058, 0.218, 0.058, color.a);

    gl_FragColor = color;
}