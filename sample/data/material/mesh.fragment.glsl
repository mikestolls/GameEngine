#version 330

in VS_OUT {
	vec3 color;
} fs_in;

out vec4 color;

uniform sampler2D Texture;

void main()
{
	color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
