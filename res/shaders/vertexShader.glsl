#version 330 core

layout (location = 0) in vec3 vertexPositionCoord;
layout (location = 1) in vec3 vertexNormalCoord;
layout (location = 2) in vec2 vertexTextureCoord;
layout(location = 3) in ivec4 boneIDs;
layout(location = 4) in vec4 weights;
layout(location = 5) in int boneCount;

out VertexShaderOut {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoord;
    vec4 fragPosLightSpace;
    vec3 vPos;
    vec3 lPos;
    vec3 shadowCoord;
} vertexShaderOut;

struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
};
uniform MVP mvp;

uniform mat4 lightSpaceMatrix;
uniform mat4 poses[100];

uniform vec3 viewPos;
uniform vec3 lightPos;

void main() {
    mat4 boneTransform = mat4(1.0f);

    for (int i = 0; i < boneCount; i++)
        boneTransform += poses[boneIDs[i]] * weights[i];

    gl_Position = mvp.projection * mvp.view * mvp.model * boneTransform * vec4(vertexPositionCoord, 1.0f);

    vertexShaderOut.fragPos = vec3(mvp.model * vec4(vertexPositionCoord, 1.0f));
    vertexShaderOut.normal = transpose(inverse(mat3(mvp.model))) * vertexNormalCoord;
    vertexShaderOut.texCoord = vertexTextureCoord;
    vertexShaderOut.fragPosLightSpace = lightSpaceMatrix * vec4(vertexShaderOut.fragPos, 1.0f);
    vertexShaderOut.vPos = viewPos;
    vertexShaderOut.lPos = lightPos;
}