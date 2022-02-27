#pragma once

static int width = 1280;
static int height = 720;

#include "vector"
#include "fstream"
#include "cstdio"

#include "imgui/imgui.h"
#include "imgui/sdl_opengl3/imgui_impl_sdl.h"
#include "imgui/sdl_opengl3/imgui_impl_opengl3.h"

#include "SDL2/SDL.h"
#include "Glew/glew.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Image.h"
#include "Texture.h"
#include "Shader.h"
#include "ShaderProgram.h"

#include "Vertex.h"
#include "Mesh.h"
#include "Model.h"
#include "ModelLoader.h"

#include "IScene.h"
#include "SceneObject.h"
#include "Camera.h"
#include "Grid.h"
#include "Scene.h"


void setupOpenGL() {
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
}

void setupSDL(SDL_Window*& window, SDL_GLContext& context) {
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

void setupImGui(SDL_Window* window, SDL_GLContext context) {
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
//
//    ImGui::StyleColorsDark();
//
//    ImGuiStyle& style = ImGui::GetStyle();
//    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//    {
//        style.WindowRounding = 0.0f;
//        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//    }
//
//    ImGui_ImplSDL2_InitForOpenGL(window, context);
//    ImGui_ImplOpenGL3_Init("#version 330 core");
}