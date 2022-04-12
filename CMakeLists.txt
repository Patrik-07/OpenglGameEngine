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

    src/Framework/Scene/Camera.h
    src/Framework/Scene/SceneObject.h
    src/Framework/Scene/Scene.h
    src/Framework/Scene/Grid.h
    src/Framework/Utility/LoadingBar.h
    src/Framework/Model/Geometry.h
    src/Framework/Utility/Resources.h
    src/Framework/Opengl/Buffer/Buffer.h
    src/Framework/Opengl/Buffer/VertexBuffer.h
    src/Framework/Opengl/Buffer/VertexBuffer.cpp
    src/Framework/Opengl/Buffer/VertexAttribute.h
    src/Framework/Opengl/Buffer/VertexAttribute.cpp
    src/Framework/Opengl/Buffer/ElementBuffer.cpp
    src/Framework/Opengl/Buffer/ElementBuffer.h
    src/Framework/Opengl/Buffer/VertexArray.cpp
    src/Framework/Opengl/Buffer/VertexArray.h
    src/Framework/Model/Geometry.cpp
    src/Framework/Opengl/Shader/Shader.cpp
    src/Framework/Opengl/Shader/ShaderProgram.cpp
    src/Framework/Model/Mesh.cpp
    src/Framework/Model/Material.cpp
    src/Framework/Opengl/Texture/Texture.cpp
    src/Framework/Model/Model.cpp
    src/Framework/ModelLoader/AssimpLoader.cpp
    src/Framework/Opengl/Uniform/Base/UniformBase.h
    src/Framework/Opengl/Uniform/UniformProvider.h
    src/Framework/ModelLoader/ModelLoader.h
    src/Framework/Opengl/Uniform/Impl/GL_F/GL_1_F.h
    src/Framework/Opengl/Uniform/Impl/GL_F/GL_2_F.h
    src/Framework/Opengl/Uniform/Impl/GL_F/GL_3_F.h
    src/Framework/Opengl/Uniform/Impl/GL_F/GL_4_F.h
    src/Framework/Opengl/Uniform/Impl/GL_I/GL_1_I.h
    src/Framework/Opengl/Uniform/Impl/GL_I/GL_2_I.h
    src/Framework/Opengl/Uniform/Impl/GL_I/GL_3_I.h
    src/Framework/Opengl/Uniform/Impl/GL_I/GL_4_I.h
    src/Framework/Opengl/Uniform/Impl/GL_UI/GL_1_UI.h
    src/Framework/Opengl/Uniform/Impl/GL_UI/GL_2_UI.h
    src/Framework/Opengl/Uniform/Impl/GL_UI/GL_3_UI.h
    src/Framework/Opengl/Uniform/Impl/GL_UI/GL_4_UI.h
    src/Framework/Opengl/Uniform/Impl/GL_F_V/GL_1_F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_F_V/GL_2_F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_F_V/GL_3_F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_F_V/GL_4_F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_I_V/GL_1_I_V.h
    src/Framework/Opengl/Uniform/Impl/GL_I_V/GL_2_I_V.h
    src/Framework/Opengl/Uniform/Impl/GL_I_V/GL_3_I_V.h
    src/Framework/Opengl/Uniform/Impl/GL_I_V/GL_4_I_V.h
    src/Framework/Opengl/Uniform/Impl/GL_UI_V/GL_1_UI_V.h
    src/Framework/Opengl/Uniform/Impl/GL_UI_V/GL_2_UI_V.h
    src/Framework/Opengl/Uniform/Impl/GL_UI_V/GL_3_UI_V.h
    src/Framework/Opengl/Uniform/Impl/GL_UI_V/GL_4_UI_V.h
    src/Framework/Opengl/Uniform/Impl/GL_MATRIX_F_V/GL_MATRIX_2F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_MATRIX_F_V/GL_MATRIX_3F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_MATRIX_F_V/GL_MATRIX_4F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_MATRIX_F_V/GL_MATRIX_2x3_F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_MATRIX_F_V/GL_MATRIX_3x2_F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_MATRIX_F_V/GL_MATRIX_2x4_F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_MATRIX_F_V/GL_MATRIX_4x3_F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_MATRIX_F_V/GL_MATRIX_3x4_F_V.h
    src/Framework/Opengl/Uniform/Impl/GL_MATRIX_F_V/GL_MATRIX_4x2_F_V.h
    src/Framework/Opengl/Uniform/Uniforms.h
    src/Framework/Opengl/Uniform/Base/UniformValue.h
    src/Framework/Opengl/Uniform/Base/MatrixUniformValue.h
    src/Framework/Opengl/Uniform/Base/ScalarUniformValue.h
    src/Framework/Opengl/Uniform/Base/VectorUniformValue.h
    src/Framework/Utility/Timer.h
    src/Framework/Utility/CameraHandler.h
    src/Framework/Utility/ImGuiRenderer.h
    src/Framework/Opengl/Buffer/FramerBuffer.h
    src/Framework/Utility/Window.h
        src/Framework/Model/VertexBoneData.h
        src/Framework/Animation/Bone.h src/Framework/Animation/AssimpGLMHelpers.h src/Framework/Animation/Animation.h src/Framework/Animation/Animator.h)

target_link_libraries(Imgui mingw32 opengl32 glew32 SDL2main SDL2 assimp)