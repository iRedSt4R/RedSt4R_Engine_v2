#version 330 core

in vec3 ourColor;
in vec2 texCoord;

out vec4 color;

uniform sampler2D DiffuseTexture;


void main()
{
    color = texture(DiffuseTexture, texCoord);
	//color.rgb = ((color.rgb - 0.5f) * max(1.8f, 0)) + 0.5f;
	//color.rgb = pow(color.rgb, vec3(1/2.2f,1/2.2f,4/2.2f));
	color.rgb *= 1.9f;
} 