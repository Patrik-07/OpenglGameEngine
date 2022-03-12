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

    include/stb/stb_image.h src/Framework/Camera.h src/Framework/SceneObject.h src/Framework/Scene.h src/Framework/SceneBase.h src/Framework/Grid.h src/Framework/LoadingBar.h src/Framework/Model/Geometry.h src/resources.h src/Framework/Opengl/Buffer/Buffer.h src/Framework/Opengl/Buffer/VertexBuffer.h src/Framework/Opengl/Buffer/VertexBuffer.cpp src/Framework/Opengl/openglFramwork.h src/Framework/Opengl/Buffer/VertexAttribute.h src/Framework/Opengl/Buffer/VertexAttribute.cpp src/Framework/Opengl/Buffer/ElementBuffer.cpp src/Framework/Opengl/Buffer/ElementBuffer.h src/Framework/Opengl/Buffer/VertexArray.cpp src/Framework/Opengl/Buffer/VertexArray.h src/Framework/Model/Geometry.cpp src/Framework/Opengl/Shader/Shader.cpp src/Framework/Opengl/Shader/ShaderProgram.cpp src/Framework/Model/Mesh.cpp src/Framework/Model/Material.cpp src/Framework/Opengl/Texture.cpp src/Framework/Model/Model.cpp src/Framework/ModelLoader/AssimpLoader.cpp src/Framework/Opengl/Shader/Uniform.h src/Framework/Opengl/Shader/UniformProvider.h src/Framework/Opengl/Shader/Uniform.cpp src/Framework/ModelLoader/ModelLoader.h)

target_link_libraries(Imgui mingw32 opengl32 glew32 SDL2main SDL2 assimp)