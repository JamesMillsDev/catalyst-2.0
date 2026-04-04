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

in vec4 vLocation;
in vec3 vNormal;

out vec4 fragColor;

void main()
{
    // Ensure normal and light direction are normalised
    vec3 N = normalize(vNormal);
    vec3 L = normalize(light.direction);

    // Calculate lambert term (negate light direction)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    // Calculate view and reflection vector
    vec3 V = normalize(cameraLocation - vLocation.xyz);
    vec3 R = reflect(L, N);

    // Calculate specular term
    float specularTerm = pow(max(0, dot(R, V)), material.specularPower);

    // Calculate colour properties
    vec3 diffuse = light.color * material.diffuseColor * lambertTerm;
    vec3 ambient = ambientLight * material.ambientColor;
    vec3 specular = light.color * material.specularColor * specularTerm;

    fragColor = vec4(ambient + diffuse + specular, 1);
}