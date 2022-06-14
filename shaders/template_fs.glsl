#version 450 core
out vec4 color;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    vec3 untex_diffuse;
    vec3 specular;
    float intensity;
    int illum;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 ScaledNormal;
in vec3 FragPos;
in vec2 TexCoords;
flat in int Highlight;
flat in int IsTextured;

#define N_POINT_LIGHTS 4
uniform PointLight pointLights[N_POINT_LIGHTS];
uniform DirectionalLight dirLight;
uniform Material material;
uniform vec3 viewPos;

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 GetMaterialProperties(const uint type);
vec3 GetMaterialDiffuse();

// Kinda like an enum but not
const uint AMBIENT = 0x00000001u;
const uint DIFFUSE = 0x00000002u;

void main() {
    // properties
    vec3 norm = normalize(ScaledNormal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < N_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

    // highlight object the player is looking at
    /* if (Highlight == 1) */
    /*     color = vec4(result, 1.0f) / vec4(0.5, 0.5, 0.5, 0.0); */
    /* else */
        color = vec4(result, 1.0f);
}

vec3 GetMaterialProperties(const uint type) {
    if (type == AMBIENT) {
        switch (material.illum) {
            case 0:         // Color on and Ambient off
                return GetMaterialDiffuse();
            case 1:         // Color on and Ambient on
                return material.ambient;
            default:
                return material.ambient;
        }
    }
    else if (type == DIFFUSE) {
        return GetMaterialDiffuse();
    }
}

vec3 GetMaterialDiffuse() {
    if (IsTextured == 1)
        return vec3(texture(material.diffuse, TexCoords));
    else
        return material.untex_diffuse;
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.intensity);

    // combine results
    vec3 ambient  = light.ambient  * GetMaterialProperties(AMBIENT);
    vec3 diffuse  = light.diffuse  * diff * GetMaterialProperties(DIFFUSE);
    vec3 specular = light.specular * spec * material.specular;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.intensity);

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
        light.quadratic * (distance * distance));

    // combine results
    vec3 ambient  = light.ambient  * GetMaterialProperties(AMBIENT);
    vec3 diffuse  = light.diffuse  * diff * GetMaterialProperties(DIFFUSE);
    vec3 specular = light.specular * spec * material.specular;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}
