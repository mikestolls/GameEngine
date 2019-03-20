#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec4 color;

uniform mat4 ProjMat;

out VS_OUT
{
	vec2 uv;
	vec4 color;
} vs_out;

void main()
{
	vs_out.uv = uv;
	vs_out.color = color;

	gl_Position = ProjMat * vec4(position.xy, 0, 1);
}