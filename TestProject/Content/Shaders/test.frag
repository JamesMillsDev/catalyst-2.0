#version 410

struct Light
{
    vec3 direction;
    vec3 color;
};

struct Material
{
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float specularPower;
};

uniform Light light;
uniform Material material;
uniform vec3 ambientLight;

uniform vec3 cameraLocation;

uniform sampler2D baseColorTex;
uniform sampler2D normalTex;
// uniform sampler2D ormTex;

in VS_OUT
{
    vec4 location;
    vec3 normal;
    vec2 uv0;
    vec3 tangent;
    vec3 biTangent;
    mat3 TBN;
} fs_in;

out vec4 fragColor;

void main()
{
    // Sample textures
    vec3 texBaseColor = texture(baseColorTex, fs_in.uv0).rgb;
    vec3 texNormal = texture(normalTex, fs_in.uv0).rgb;

    // Ensure vectors are normalized
    vec3 T = normalize(fs_in.tangent);
    vec3 B = normalize(fs_in.biTangent);
    vec3 N = fs_in.TBN * (texNormal * 2 - 1);
    vec3 L = normalize(light.direction);

    // Calculate lambert term (negate light direction)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    // Calculate view and reflection vector
    vec3 V = normalize(cameraLocation - fs_in.location.xyz);
    vec3 R = reflect(L, N);

    // Calculate specular term
    float specularTerm = pow(max(0, dot(R, V)), material.specularPower);

    // Calculate colour properties
    vec3 diffuse = light.color * material.diffuseColor * lambertTerm * texBaseColor;
    vec3 ambient = ambientLight * material.ambientColor * texBaseColor;
    vec3 specular = light.color * material.specularColor * specularTerm;

    fragColor = vec4(diffuse + ambient + specular, 1);
}