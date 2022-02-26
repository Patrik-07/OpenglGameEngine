#version 330 core

out vec3 nearPoint;
out vec3 farPoint;
out mat4 view;
out mat4 projection;
out vec3 cameraPosition;

struct MVP {
    mat4 view;
    mat4 projection;
};
uniform MVP mvp;
uniform vec3 cameraPos;

vec3 unprojectPoint(float x, float y, float z, mat4 view, mat4 projection) {
    mat4 viewInv = inverse(view);
    mat4 projInv = inverse(projection);
    vec4 unprojectedPoint =  viewInv * projInv * vec4(x, y, z, 1.0f);
    return unprojectedPoint.xyz / unprojectedPoint.w;
}

const vec2 grid[4] = {
    vec2(-1.0, -1.0),
    vec2(1.0, -1.0),
    vec2(-1.0, 1.0),
    vec2(1.0, 1.0)
};
void main() {
    vec3 pos = vec3(grid[gl_VertexID].x, grid[gl_VertexID].y, 0.0f);

    nearPoint = unprojectPoint(pos.x, pos.y, 0.0f, mvp.view, mvp.projection);
    farPoint = unprojectPoint(pos.x, pos.y, 1.0f, mvp.view, mvp.projection);

    view = mvp.view;
    projection = mvp.projection;
    cameraPosition = cameraPos;

    gl_Position = vec4(pos, 1.0f);
}