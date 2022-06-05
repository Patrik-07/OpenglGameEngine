#version 330 core

in VertexShaderOut {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoord;
    vec4 fragPosLightSpace;
    vec3 vPos;
    vec3 lPos;
    vec3 shadowCoord;
} fragmentShaderIn;

out vec4 FragColor;

//uniform Material material;
uniform bool enableTexture;
uniform bool enableNormal;
uniform bool enableSolid;

uniform sampler2D diffuseMap;
uniform sampler2D depthMap;

float ShadowCalculation(vec4 fragPosLightSpace, float bias) {
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5f + 0.5f;

    float closestDepth = texture(depthMap, projCoords.xy).z;
    float currentDepth = projCoords.z;

    float shadow = currentDepth - bias > closestDepth ? 0.75f : 0.0f;

    if(projCoords.z > 1.0f)
        shadow = 0.0f;

    return 1.0f - shadow;
}

void main() {
    if (enableTexture) {
        vec3 color = texture(diffuseMap, fragmentShaderIn.texCoord).rgb;
        vec3 normal = normalize(fragmentShaderIn.normal);
        vec3 lightColor = vec3(1.0f);

        // ambient
        vec3 ambient = 0.2f * lightColor;

        // diffuse
        vec3 lightDir = normalize(fragmentShaderIn.lPos - fragmentShaderIn.fragPos);
        float diff = max(dot(lightDir, normal), 0.0f);
        vec3 diffuse = diff * lightColor;

        // specular
        vec3 viewDir = normalize(fragmentShaderIn.vPos - fragmentShaderIn.fragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normal, halfwayDir), 0.0f), 2.0f);
        vec3 specular = spec * lightColor;

        // shadow
        float bias = max(0.05f * (1.0f - dot(normal, lightDir)), 0.025f);
        float shadow = ShadowCalculation(fragmentShaderIn.fragPosLightSpace, bias);
        vec3 lighting = (ambient + shadow * (diffuse + specular)) * color;

        if (enableNormal) {
            FragColor = vec4(normal, 1.0f);
        } else if (enableSolid) {
            FragColor = vec4(color, 1.0f);
        } else {
            FragColor = vec4(lighting, 1.0f);
        }
    } else FragColor = vec4(0.83f, 0.36f, 0.36f, 1.0f);
}