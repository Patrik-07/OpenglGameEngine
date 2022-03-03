#version 330 core

out vec2 textureCoord;
out vec3 near;
out vec3 far;

struct MVP {
    mat4 view;
    mat4 projection;
};
uniform MVP mvp;

const vec2 grid[4] = {
    vec2(-1.0, -1.0),
    vec2(1.0, -1.0),
    vec2(-1.0, 1.0),
    vec2(1.0, 1.0)
};

const vec2 texCoord[4] = {
    vec2(-1.0, -1.0),
    vec2(1.0, -1.0),
    vec2(-1.0, 1.0),
    vec2(1.0, 1.0)
};

vec3 unprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0f);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

void main() {
    nearPoint = unprojectPoint(pos.x, pos.y, 0.0f, mvp.view, mvp.projection);
    farPoint = unprojectPoint(pos.x, pos.y, 1.0f, mvp.view, mvp.projection);
    textureCoord = texCoord[gl_VertexID];

    gl_Position = vec4(grid[gl_VertexID].x, 0.0f, grid[gl_VertexID].y, 1.0f);
}