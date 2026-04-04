#version 410

in vec3 vNormal;

uniform vec3 lightDirection;

out vec4 fragColor;

void main()
{
    // Ensure normal and light direction are normalised
    vec3 N = normalize(vNormal);
    vec3 L = normalize(lightDirection);

    // Calculate lambert term (negate light direction)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    fragColor = vec4(lambertTerm, lambertTerm, lambertTerm, 1);
}