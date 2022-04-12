#version 330 core

layout (location = 0) in vec3 vertexPositionCoord;
layout (location = 1) in vec3 vertexNormalCoord;
layout (location = 2) in vec2 vertexTextureCoord;
layout(location = 5) in ivec4 boneIDs;
layout(location = 6) in vec4 weights;

out vec2 texCoord;

struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
};
uniform MVP mvp;

const int maxBoneCount = 100;
uniform mat4 poses[maxBoneCount];

void main() {
    mat4 boneTransform = mat4(1.0f);
    for (int i = 0; i < 4; i++) {
        if (boneIDs[i] == -1)
            continue;
        boneTransform += poses[boneIDs[i]] * weights[i];
    }
    vec4 finalPosition = boneTransform * vec4(vertexPositionCoord, 1.0f);

    gl_Position = mvp.projection * mvp.view * mvp.model * finalPosition;
    texCoord = vertexTextureCoord;
}