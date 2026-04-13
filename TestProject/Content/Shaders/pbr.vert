#version 410

layout(location=0) in vec4 location;
layout(location=1) in vec4 normal;
layout(location=2) in vec2 uv0;
layout(location=11) in vec4 tangent;

out VS_OUT
{
    vec4 location;
    vec3 worldLocation;
    vec3 normal;
    vec2 uv0;
    vec3 tangent;
    vec3 biTangent;
    mat3 TBN;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vs_out.uv0 = uv0;
    vs_out.location = model * location;
    vs_out.worldLocation = vec3(model * location);
    vs_out.normal = (model * normal).xyz;
    vs_out.tangent = (model * vec4(tangent.xyz, 0)).xyz;
    vs_out.biTangent = cross(vs_out.normal, vs_out.tangent) * tangent.w;

    vec3 T = normalize(vs_out.tangent);
    vec3 B = normalize(vs_out.biTangent);
    vec3 N = normalize(vs_out.normal);

    vs_out.TBN = mat3(T, B, N);

    gl_Position = projection * view * model * location;
}