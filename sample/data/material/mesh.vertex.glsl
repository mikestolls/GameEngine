#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 ProjMat;
uniform mat4 ModelMat;
uniform mat4 ViewMat;

out VS_OUT {
	vec3 color;
} vs_out;

void main()
{
	vs_out.color = color;

	gl_Position = ProjMat * ViewMat * ModelMat * vec4(position.xyz, 1);
}