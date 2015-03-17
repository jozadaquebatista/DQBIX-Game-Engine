#version 120
uniform sampler2D diffuse;
uniform sampler2D normal;

uniform vec2 Resolution;
uniform vec3 LightPos;
uniform vec4 LightColor;
uniform vec4 AmbientColor;
uniform vec3 Falloff;

varying vec2 texcoord;

void main()
{
	vec4 diffuseColor = texture2D(diffuse, texcoord);
	vec3 normalMap = texture2D(normal, texcoord).xyz;

	vec3 lightDir = vec3(LightPos.xy - (gl_FragCoord.xy / Resolution.xy), LightPos.z);
	lightDir.x *= Resolution.x / Resolution.y;

	float D = length(lightDir);

	vec3 N = normalize(normalMap * 2.0 - 1.0);
    vec3 L = normalize(lightDir);

	vec3 diffusePremul = (LightColor.rgb * LightColor.a) * max(dot(N, L), 0.0);

	vec3 Ambient = AmbientColor.rgb * AmbientColor.a;
	float Attenuation = 1.0 / ( Falloff.x + (Falloff.y*D) + (Falloff.z*D*D) );

	vec3 Intensity = Ambient + diffusePremul * Attenuation;
    vec3 FinalColor = diffuseColor.rgb * Intensity;

    gl_FragColor = vColor * vec4(FinalColor, diffuseColor.a);
}