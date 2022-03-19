#version 330 core

out vec3 near;
out vec3 far;
out mat4 view;
out mat4 projection;
out vec3 vertexPosition;
out vec3 cameraPosition;

struct Camera {
    vec3 position;
    mat4 view;
    mat4 projection;
};
uniform Camera camera;

const vec2 grid[4] = {
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
    vec3 pos = vec3(grid[gl_VertexID].x, grid[gl_VertexID].y, 0.0f);

    near = unprojectPoint(pos.x, pos.y, 0.0f, camera.view, camera.projection);
    far = unprojectPoint(pos.x, pos.y, 1.0f, camera.view, camera.projection);
    view = camera.view;
    projection = camera.projection;
    vertexPosition = pos;
    cameraPosition = camera.position;

    gl_Position = vec4(pos, 1.0f);
}