#pragma once

namespace RESOURCE {
    namespace SHADER {
        const char* DEFAULT_VS = R"(shaders\defaultVertexShader.glsl)";
        const char* DEFAULT_FS = R"(shaders\defaultFragmentShader.glsl)";

        const char* GRID_VS = R"(shaders\gridVertexShader.glsl)";
        const char* GRID_FS = R"(shaders\gridFragmentShader.glsl)";

        const char* DEPTH_VS = R"(shaders\depthVertexShader.glsl)";
        const char* DEPTH_FS = R"(shaders\depthFragmentShader.glsl)";
    }

    namespace MODEL {
        const char* DUCK = R"(models\duck\10602_Rubber_Duck_v1_L3.obj)";
//        const char* FOX = R"(models\fox\Fox.gltf)";
        const char* FOX = R"(models\fox2\untitled.gltf)";
        const char* PLANE = R"(models\plane\plane.gltf)";
        const char* GITHUB = R"(models\github\Patrik-07-2022.stl)";
    }
}