#version 330 core

in vec3 near;
in vec3 far;
in mat4 view;
in mat4 projection;
in vec3 vertexPosition;
in vec3 cameraPosition;

out vec4 color;

vec4 grid(vec3 fragPos3D, float scale, bool drawAxis) {
    vec2 coord = fragPos3D.xz * scale;
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5f) - 0.5f) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(0.3f, 0.3f, 0.3f, 1.0f - min(line, 1.0f));
    if (fragPos3D.x > -0.1f * minimumx && fragPos3D.x < 0.1f * minimumx) {
        color.y = 1.0f;
    }
    if (fragPos3D.z > -0.1 * minimumz && fragPos3D.z < 0.1f * minimumz) {
        color.z = 1.0f;
    }
    return color;
}

float computeDepth(vec3 pos) {
    vec4 clip_space_pos = projection * view * vec4(pos.xyz, 1.0f);
    float clip_space_depth = clip_space_pos.z / clip_space_pos.w;

    float far = gl_DepthRange.far;
    float near = gl_DepthRange.near;

    float depth = (((far-near) * clip_space_depth) + near + far) / 2.0f;

    return depth;
}

void main() {
    float t = -near.y / (far.y-near.y);
    vec3 fragPos3D = near + t * (far - near);

    vec4 vertexPos = projection * view * vec4(fragPos3D, 1.0f);
    vec4 cameraPos = projection * view * vec4(cameraPosition, 1.0f);
    float d = length(cameraPos - vertexPos);
    float opacity = clamp(d / 250, 0, 1);

    vec3 R = near + t * (far-near);
    gl_FragDepth = computeDepth(R);

    color = (grid(fragPos3D, 10, true) + grid(fragPos3D, 1, true)) * float(t > 0.0f);
    color.a *= 1 - opacity;
}