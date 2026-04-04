#version 410

layout(location=0) in vec4 location;
layout(location=1) in vec4 normal;

out vec4 vLocation;
out vec3 vNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vLocation = model * location;
    vNormal = (model * normal).xyz;
    gl_Position = projection * view * model * location;
}