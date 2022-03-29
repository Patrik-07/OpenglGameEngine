#pragma once

namespace RESOURCE {
    namespace SHADER {
        const char* DEFAULT_VS = R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\shaders\vertexShader.glsl)";
        const char* DEFAULT_FS = R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\shaders\fragmentShader.glsl)";
    }

    namespace MODEL {
        const char* DUCK = R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\duck\10602_Rubber_Duck_v1_L3.obj)";
        const char* FOX = R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\fox\Fox.gltf)";

        namespace RPG_CHARACTER {
            const char* MODEL = R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\Models\rpg_character\RPG Character Mecanim Animation Pack FREE\Models\Characters\untitled.fbx)";
            const char* BONES = R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\Models\rpg_character\RPG Character Mecanim Animation Pack FREE\Models\Characters\RPG-Character-Bones.FBX)";

            namespace ANIMATION {
                const char* RUN = R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\Models\rpg_character\RPG Character Mecanim Animation Pack FREE\Animations\Unarmed\RPG-Character@Unarmed-Run-Forward.FBX)";
            }
        }
    }
}