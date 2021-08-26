#version 400
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NUM_POINT_LIGHTS 8

uniform Material material;
uniform DirLight dirLight;
uniform int NumLights;
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform vec3 viewPos;
uniform bool LightOn;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);  
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  

//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
//    // Ambient
//    vec3 ambient = dirLight.ambient * material.ambient;
//  	
//    // Diffuse 
//    vec3 lightDir = normalize(-dirLight.direction);
//    float diff = max(dot(normal, lightDir), 0.0);
//    vec3 diffuse = dirLight.diffuse * (diff * material.diffuse);
//    
//    // Specular
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    vec3 specular = dirLight.specular * (spec * material.specular);  
//        
//    vec3 result = ambient + diffuse + specular;
//
//    return result;
//};


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
//    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);

    return ambient + diffuse + specular;
};

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
//    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
};

void main()
{
    if (LightOn) {
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);

        // Directional light
        vec3 result = CalcDirLight(dirLight, norm, viewDir);
        // Point lighting
        for (int i = 0; i < NumLights; i++) {
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
        }

        FragColor = vec4(result, 1.0);

    } else {
        float ambientStrength = 0.2f;
        vec3 ambient =  material.ambient * ambientStrength;
        vec3 diffuse = material.diffuse;
        vec3 result = ambient + diffuse;
        FragColor = vec4(result, 1.0);
    }
}
