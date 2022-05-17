#pragma once

static int width = 1800;
static int height = 900;

#include "imgui/imgui.h"
#include "imgui/sdl_opengl3/imgui_impl_sdl.h"
#include "imgui/sdl_opengl3/imgui_impl_opengl3.h"

#include "SDL2/SDL.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

// Opengl includes
#include "Opengl/Buffer/VertexArray.h"
#include "Opengl/Buffer/VertexBuffer.h"
#include "Opengl/Buffer/ElementBuffer.h"
#include "Opengl/Buffer/FramerBuffer.h"

#include "Opengl/Shader/Shader.h"
#include "Opengl/Shader/ShaderProgram.h"

#include "Opengl/Texture/Texture.h"

// model includes
#include "model/Model.h"

// AssimpLoader includes
#include "loader/modelLoader/ModelLoader.h"
#include "loader/modelLoader/AssimpLoader.h"

#include "Scene/SceneObject.h"
#include "Scene/Camera.h"
#include "Scene/Grid.h"
#include "Scene/Scene.h"

#include "Utility/Timer.h"
#include "Utility/CameraHandler.h"
#include "Utility/LoadingBar.h"
#include "Utility/ImGuiRenderer.h"

#include "Utility/Resources.h"

void initSDL(SDL_Window*& window, SDL_GLContext& context) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("OpenGL_game_engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SetSwapInterval(1);
}

void initOpenGL() {
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool processEvent(SDL_Event event) {
    ImGui_ImplSDL2_ProcessEvent(&event);
    if (event.type == SDL_QUIT)
        return false;
    return true;
}

ImGuiRenderer init(SDL_Window*& window, SDL_GLContext& context) {
    initSDL(window, context);
    initOpenGL();
    return ImGuiRenderer(window, context);
}