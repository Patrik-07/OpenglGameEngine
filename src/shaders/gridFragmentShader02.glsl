#version 330 core

in vec3 nearPoint;
in vec3 farPoint;

in mat4 view;
in mat4 projection;

in vec3 cameraPosition;

out vec4 FragColor;

vec4 grid(vec3 fragPos3D, float scale, bool drawAxis) {
    vec2 coord = fragPos3D.xz * scale;
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(fract(coord - 0.5) - 0.5) / derivative;
    float line = min(grid.x, grid.y);
    float minimumz = min(derivative.y, 1);
    float minimumx = min(derivative.x, 1);
    vec4 color = vec4(0.2, 0.2, 0.2, 1.0 - min(line, 1.0));
    // z axis
    if(fragPos3D.x > -0.1 * minimumx && fragPos3D.x < 0.1 * minimumx)
    color.z = 1.0;
    // x axis
    if(fragPos3D.z > -0.1 * minimumz && fragPos3D.z < 0.1 * minimumz)
    color.x = 1.0;
    return color;
}

float computeDepth(vec3 pos) {
    vec4 clip_space_pos = projection * view * vec4(pos, 1.0);
    return (clip_space_pos.z / clip_space_pos.w);
}

float computeLinearDepth(vec3 pos) {
    vec4 clip_space_pos = projection * view * vec4(pos, 1.0);
    float clip_space_depth = (clip_space_pos.z / clip_space_pos.w) * 2.0 - 1.0; // put back between -1 and 1
    float linearDepth = (2.0 * 0.01f * 10.0f) / (10.0f +  0.01f - clip_space_depth * (10.0f -  0.01f)); // get linear value between 0.01 and 100
    return linearDepth /  0.01f; // normalize
}

void main() {
    float t = -nearPoint.y / (farPoint.y - nearPoint.y);
    vec3 fragPos3D = nearPoint + t * (farPoint - nearPoint);

    gl_FragDepth = computeDepth(fragPos3D);

    vec4 clip_space_pos = projection * view * vec4(fragPos3D, 1.0);
    float d = length(vec4(cameraPosition, 1.0f) - (clip_space_pos));
    float opacity = clamp(d / 100, 0, 1);

    FragColor = (grid(fragPos3D, 10, true) + grid(fragPos3D, 1, true)) * float(t > 0);
    FragColor.a *= 1.0f - opacity;
}