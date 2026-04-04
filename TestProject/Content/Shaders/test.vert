#version 410

layout(location=0) in vec4 location;
layout(location=1) in vec4 normal;

out vec3 vNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vNormal = (model * normal).xyz;
    gl_Position = projection * view * model * location;
}