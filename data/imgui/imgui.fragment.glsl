#version 330

in VS_OUT {
	vec2 uv;
	vec4 color;
} fs_in;

out vec4 color;

uniform sampler2D Texture;

void main()
{
	color = fs_in.color * texture(Texture, fs_in.uv.st);
}
