#version 400
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;
uniform bool LightOn;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;


void main()
{
    if (LightOn) {
        // Ambient
//        vec3 ambient = light.ambient * material.ambient;

        // Diffuse
//        vec3 norm = normalize(Normal);
//        vec3 lightDir = normalize(-light.direction);
//        float diff = max(dot(norm, lightDir), 0.0);
//        vec3 diffuse = light.diffuse * ( diff * material.diffuse);

        //Specular
//        vec3 viewDir = normalize(viewPos - FragPos);
//        vec3 reflectDir = reflect(-lightDir, norm);
//        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//        vec3 specular = light.specular * (spec * material.specular);  

//        // spotlight (soft edges)
//        float theta = dot(lightDir, normalize(-light.direction)); 
//        float epsilon = (light.cutOff - light.outerCutOff);
//        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
//        diffuse  *= intensity;
//        specular *= intensity;

        // Attenuation
//        float distance = length(light.position - FragPos);
//        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
//        ambient *= attenuation; 
//        diffuse *= attenuation;
//        specular *= attenuation;  
            
//        vec3 result = ambient + diffuse + specular;
//        FragColor = vec4(result, 1.0);   

        // Directional light
        // Ambient
        vec3 ambient = light.ambient * material.ambient;
  	
        // Diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDirChange = vec3(-light.direction.x, -light.direction.y, -light.direction.z);
        vec3 lightDir = normalize(lightDirChange);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
        // Specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * (spec * material.specular);  
        
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);

    } else {
        float ambientStrength = 0.2f;
        vec3 ambient =  material.ambient * ambientStrength;
        vec3 diffuse = material.diffuse;
        vec3 result = ambient + diffuse;
        FragColor = vec4(result, 1.0);
    }
}