cmake_minimum_required(VERSION 3.21)
project(Imgui)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(lib)

add_executable(Imgui
    src/main.cpp

    include/imgui/imconfig.h
    include/imgui/imgui.cpp
    include/imgui/imgui.h
    include/imgui/imgui_demo.cpp
    include/imgui/imgui_draw.cpp
    include/imgui/imgui_internal.h
    include/imgui/imgui_tables.cpp
    include/imgui/imgui_widgets.cpp
    include/imgui/imstb_rectpack.h
    include/imgui/imstb_textedit.h
    include/imgui/imstb_truetype.h
    include/imgui/sdl_opengl3/imgui_impl_opengl3.cpp
    include/imgui/sdl_opengl3/imgui_impl_opengl3.h
    include/imgui/sdl_opengl3/imgui_impl_opengl3_loader.h
    include/imgui/sdl_opengl3/imgui_impl_sdl.cpp
    include/imgui/sdl_opengl3/imgui_impl_sdl.h

    include/stb/stb_image.h

    src/framework/scene/Camera.h
    src/framework/scene/SceneObject.h
    src/framework/scene/Scene.h
    src/framework/scene/Grid.h
    src/framework/utility/LoadingBar.h
    src/framework/model/Geometry.h
    src/framework/utility/Resources.h
    src/framework/opengl/buffer/Buffer.h
    src/framework/opengl/buffer/VertexBuffer.h
    src/framework/opengl/buffer/VertexBuffer.cpp
    src/framework/opengl/buffer/VertexAttribute.h
    src/framework/opengl/buffer/VertexAttribute.cpp
    src/framework/opengl/buffer/ElementBuffer.cpp
    src/framework/opengl/buffer/ElementBuffer.h
    src/framework/opengl/buffer/VertexArray.cpp
    src/framework/opengl/buffer/VertexArray.h
    src/framework/model/Geometry.cpp
    src/framework/opengl/shader/Shader.cpp
    src/framework/opengl/shader/ShaderProgram.cpp
    src/framework/model/Mesh.cpp
    src/framework/model/Material.cpp
    src/framework/opengl/texture/Texture.cpp
    src/framework/model/Model.cpp
    src/framework/loader/modelLoader/AssimpLoader.cpp
    src/framework/opengl/uniform/base/UniformBase.h
    src/framework/opengl/uniform/UniformProvider.h
    src/framework/loader/modelLoader/ModelLoader.h
    src/framework/opengl/uniform/impl/GL_F/GL_1_F.h
    src/framework/opengl/uniform/impl/GL_F/GL_2_F.h
    src/framework/opengl/uniform/impl/GL_F/GL_3_F.h
    src/framework/opengl/uniform/impl/GL_F/GL_4_F.h
    src/framework/opengl/uniform/impl/GL_I/GL_1_I.h
    src/framework/opengl/uniform/impl/GL_I/GL_2_I.h
    src/framework/opengl/uniform/impl/GL_I/GL_3_I.h
    src/framework/opengl/uniform/impl/GL_I/GL_4_I.h
    src/framework/opengl/uniform/impl/GL_UI/GL_1_UI.h
    src/framework/opengl/uniform/impl/GL_UI/GL_2_UI.h
    src/framework/opengl/uniform/impl/GL_UI/GL_3_UI.h
    src/framework/opengl/uniform/impl/GL_UI/GL_4_UI.h
    src/framework/opengl/uniform/impl/GL_F_V/GL_1_F_V.h
    src/framework/opengl/uniform/impl/GL_F_V/GL_2_F_V.h
    src/framework/opengl/uniform/impl/GL_F_V/GL_3_F_V.h
    src/framework/opengl/uniform/impl/GL_F_V/GL_4_F_V.h
    src/framework/opengl/uniform/impl/GL_I_V/GL_1_I_V.h
    src/framework/opengl/uniform/impl/GL_I_V/GL_2_I_V.h
    src/framework/opengl/uniform/impl/GL_I_V/GL_3_I_V.h
    src/framework/opengl/uniform/impl/GL_I_V/GL_4_I_V.h
    src/framework/opengl/uniform/impl/GL_UI_V/GL_1_UI_V.h
    src/framework/opengl/uniform/impl/GL_UI_V/GL_2_UI_V.h
    src/framework/opengl/uniform/impl/GL_UI_V/GL_3_UI_V.h
    src/framework/opengl/uniform/impl/GL_UI_V/GL_4_UI_V.h
    src/framework/opengl/uniform/impl/GL_MATRIX_F_V/GL_MATRIX_2F_V.h
    src/framework/opengl/uniform/impl/GL_MATRIX_F_V/GL_MATRIX_3F_V.h
    src/framework/opengl/uniform/impl/GL_MATRIX_F_V/GL_MATRIX_4F_V.h
    src/framework/opengl/uniform/impl/GL_MATRIX_F_V/GL_MATRIX_2x3_F_V.h
    src/framework/opengl/uniform/impl/GL_MATRIX_F_V/GL_MATRIX_3x2_F_V.h
    src/framework/opengl/uniform/impl/GL_MATRIX_F_V/GL_MATRIX_2x4_F_V.h
    src/framework/opengl/uniform/impl/GL_MATRIX_F_V/GL_MATRIX_4x3_F_V.h
    src/framework/opengl/uniform/impl/GL_MATRIX_F_V/GL_MATRIX_3x4_F_V.h
    src/framework/opengl/uniform/impl/GL_MATRIX_F_V/GL_MATRIX_4x2_F_V.h
    src/framework/opengl/uniform/Uniforms.h
    src/framework/opengl/uniform/base/UniformValue.h
    src/framework/opengl/uniform/base/MatrixUniformValue.h
    src/framework/opengl/uniform/base/ScalarUniformValue.h
    src/framework/opengl/uniform/base/VectorUniformValue.h
    src/framework/utility/Timer.h
    src/framework/utility/CameraHandler.h
    src/framework/utility/ImGuiRenderer.h
    src/framework/opengl/buffer/FramerBuffer.h
    src/framework/utility/Window.h
    src/framework/model/VertexBoneData.h
    src/framework/animation/Bone.h
    src/framework/animation/AssimpGLMHelpers.h
    src/framework/animation/Animation.h
    src/framework/animation/Animator.h
    src/framework/animation/Keyframe.h
    src/framework/model/animatedModel/Skeleton.h
    src/framework/animation/Pose.h
    src/framework/animation/AnimationContainer.h
    src/framework/anim/Bone2.h
    src/framework/anim/Keyframe.h
    src/framework/anim/KeyValue.h
    src/framework/model/animatedModel/AnimatedModel.h
    src/framework/anim/VertexData.h
    src/framework/animation/Timeline.h
    src/framework/opengl/buffer/DepthBuffer.h
)

target_link_libraries(Imgui mingw32 opengl32 glew32 SDL2main SDL2 assimp)