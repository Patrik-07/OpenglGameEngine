#pragma once

static int width = 1920;
static int height = 900;

#include "imgui/imgui.h"
#include "imgui/sdl_opengl3/imgui_impl_sdl.h"
#include "imgui/sdl_opengl3/imgui_impl_opengl3.h"

#include "SDL2/SDL.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "LoadingBar.h"

#include "Utility/ImGuiRenderer.h"

// Opengl includes
#include "Opengl/Buffer/VertexArray.h"
#include "Opengl/Buffer/VertexBuffer.h"
#include "Opengl/Buffer/ElementBuffer.h"

#include "Opengl/Shader/Shader.h"
#include "Opengl/Shader/ShaderProgram.h"

#include "Opengl/Texture.h"

// Model includes
#include "Model/Model.h"

// AssimpLoader includes
#include "ModelLoader/ModelLoader.h"
#include "ModelLoader/AssimpLoader.h"

#include "Scene/SceneObject.h"
#include "Scene/Camera.h"
#include "Scene/Grid.h"
#include "Scene/Scene.h"
#include "Opengl/Buffer/FramerBuffer.h"

unsigned int FBO;
unsigned int frameBufferTextureID;
unsigned int frameBufferDepthID;

//FrameBuffer* frameBuffer;

void setupOpenGL() {
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

ImGuiRenderer init(SDL_Window*& window, SDL_GLContext& context) {
    setupSDL(window, context);
    setupOpenGL();
    return ImGuiRenderer(window, context);
}

void sceneRender(Scene& scene) {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glViewport(0, 0, scene.width, scene.height);
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.update();
    scene.draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::Begin("Scene");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    scene.hasFocus = ImGui::IsWindowFocused();
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddImage(
        (void*)frameBufferTextureID,
        pos,
        ImVec2(pos.x + (float)scene.width, pos.y + (float)scene.height),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );
    ImGui::End();
}