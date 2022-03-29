#version 330 core
layout (location = 0) in vec3 vertexPositionCoord;
layout (location = 1) in vec3 vertexNormalCoord;
layout (location = 2) in vec2 vertexTextureCoord;
layout(location = 5) in ivec4 bones;
layout(location = 6) in vec4 weights;

out vec2 texCoord;

struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
};
uniform MVP mvp;

const int maxBoneCount = 100;
const int maxBonePerVertex = 4;
uniform mat4 pose[maxBoneCount];

void main() {
    vec4 finalPosition = vec4(0.0f);
    for (int i = 0; i < maxBonePerVertex; i++) {
        if (bones[i] == -1)
            continue;
        if (bones[i] >= 4) {
            finalPosition = vec4(vertexPositionCoord, 1.0f);
            break;
        }
        vec4 bonePosition = pose[bones[i]] * vec4(vertexPositionCoord, 1.0f);
        finalPosition += bonePosition * weights[i];
    }

    gl_Position = mvp.projection * mvp.view * mvp.model * vec4(vertexPositionCoord, 1.0f);
    texCoord = vertexTextureCoord;
}