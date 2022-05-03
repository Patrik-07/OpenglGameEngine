#pragma once

namespace RESOURCE {
    namespace SHADER {
        const char* DEFAULT_VS = R"(shaders\vertexShader.glsl)";
        const char* DEFAULT_FS = R"(shaders\fragmentShader.glsl)";

        const char* GRID_VS = R"(shaders\gridVertexShader.glsl)";
        const char* GRID_FS = R"(shaders\gridFragmentShader.glsl)";
    }

    namespace MODEL {
        const char* DUCK = R"(models\duck\10602_Rubber_Duck_v1_L3.obj)";
        const char* FOX = R"(models\fox\Fox.gltf)";
    }
}