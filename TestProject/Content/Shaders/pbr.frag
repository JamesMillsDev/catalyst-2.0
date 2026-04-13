#version 410

struct Light
{
    vec3 location;
    vec3 direction;
    vec3 color;

    int isSet;
    int isDirectional;
};

struct Material
{
    vec3 baseColor;

    sampler2D baseColorTex;
    sampler2D normalTex;
    sampler2D ormTex;
};

in VS_OUT
{
    vec4 location;
    vec3 worldLocation;
    vec3 normal;
    vec2 uv0;
    vec3 tangent;
    vec3 biTangent;
    mat3 TBN;
} fs_in;

const int MAX_LIGHTS = 4;

uniform Light lights[MAX_LIGHTS];
uniform Material material;
//uniform vec3 ambientLight;

uniform vec3 cameraLocation;

const float PI = 3.14159265359;

out vec4 fragColor;

vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);

    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 GetNormal()
{
    vec3 texNormal = texture(material.normalTex, fs_in.uv0).rgb;
    return fs_in.TBN * (texNormal * 2 - 1);
}

void main()
{
    vec3 baseColor = pow(texture(material.baseColorTex, fs_in.uv0).rgb, vec3(2.2));
    vec3 orm = texture(material.ormTex, fs_in.uv0).rgb;

    float ao = orm.r;
    float roughness = orm.g;
    float metallic = orm.b;

    vec3 N = GetNormal();
    vec3 V = normalize(cameraLocation - fs_in.worldLocation);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, baseColor, metallic);

    // Reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < MAX_LIGHTS; ++i)
    {
        Light light = lights[i];

        if(light.isSet == 1)
        {
            // Handle directional and spot
            vec3 L = vec3(0.0);
            if(light.isDirectional == 1)
            {
                L = normalize(light.direction);
            }
            else
            {
                L = normalize(light.location - fs_in.worldLocation);
            }

            // Calculate per-light radiance
            vec3 H = normalize(V + L);
            float dist = length(light.location - fs_in.worldLocation);
            float attenuation = 1.0 / (dist * dist);
            vec3 radiance = light.color * attenuation;

            // Cook-Torrance BRDF
            float NDF = DistributionGGX(N, H, roughness);
            float G = GeometrySmith(N, V, L, roughness);
            vec3 F = FresnelSchlick(max(dot(H, V), 0.0), F0);

            vec3 numerator = NDF * G * F;
            float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by 0
            vec3 specular = numerator / denominator;

            // kS is equal to Fresnel
            vec3 kS = F;
            // For energy conversation, the diffuse and specular light can't
            // be above 1.0 (unless the surface emits light); to preserve this
            // relationship the diffuse component (kD) should equal 1.0 - kS
            vec3 kD = vec3(1.0) - kS;
            // Multiply kD by the inverse metalness such that only non-metals
            // have diffuse lighting, or a linear blend if partly metal (pure
            // metals have no diffuse light)
            kD *= 1.0 - metallic;

            // scale light by NdotL
            float NdotL = max(dot(N, L), 0.0);

            // add to ongoing radiance Lo
            // not that we already multiplied by the BRDF by the Fresnel (kS) so we won't multiply by kS again
            Lo += (kD * baseColor / PI + specular) * radiance * NdotL;
        }
    }

    // ambient lighting
    vec3 ambient = vec3(0.03) * material.baseColor * ao;

    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0 / 2.2));

    fragColor = vec4(color, 1.0);
}