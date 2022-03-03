cmake_minimum_required(VERSION 3.21)
project(Imgui)

set(CMAKE_CXX_STANDARD 14)

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

    include/stb/stb_image.h include/framework/Camera.h include/framework/SceneObject.h include/framework/Scene.h include/framework/IScene.h include/framework/EventHandler.h include/framework/Grid.h)

target_link_libraries(Imgui mingw32 opengl32 glew32 SDL2main SDL2 assimp)