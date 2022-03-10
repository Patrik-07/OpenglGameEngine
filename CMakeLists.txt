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

    include/stb/stb_image.h include/Framework/Camera.h include/Framework/SceneObject.h include/Framework/Scene.h include/Framework/IScene.h include/Framework/Grid.h include/Framework/LoadingBar.h include/Framework/Model/Geometry.h src/resources.h include/Framework/Opengl/Buffer/Buffer.h include/Framework/Opengl/Buffer/VertexBuffer.h include/Framework/Opengl/Buffer/VertexBuffer.cpp include/Framework/Opengl/openglFramwork.h include/Framework/Opengl/Buffer/VertexAttribute.h include/Framework/Opengl/Buffer/VertexAttribute.cpp include/Framework/Opengl/Buffer/ElementBuffer.cpp include/Framework/Opengl/Buffer/ElementBuffer.h include/Framework/Opengl/Buffer/VertexArray.cpp include/Framework/Opengl/Buffer/VertexArray.h include/Framework/Model/Geometry.cpp include/Framework/Opengl/Shader/Shader.cpp include/Framework/Opengl/Shader/ShaderProgram.cpp include/Framework/Model/Mesh.cpp include/Framework/Model/Material.cpp include/Framework/Opengl/Texture.cpp include/Framework/Model/Model.cpp include/Framework/ModelLoader/ModelLoader.cpp)

target_link_libraries(Imgui mingw32 opengl32 glew32 SDL2main SDL2 assimp)