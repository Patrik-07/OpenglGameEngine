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

#include "SceneBase.h"
#include "SceneObject.h"
#include "Camera.h"
#include "Grid.h"
#include "Scene.h"

unsigned int FBO;
unsigned int frameBufferTextureID;
unsigned int frameBufferDepthID;
bool opened;

void setupOpenGL() {
    glewExperimental = GL_TRUE;
    glewInit();

    glViewport(0, 0, width, height);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &frameBufferTextureID);
    glBindTexture(GL_TEXTURE_2D, frameBufferTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTextureID, 0);

//    glGenRenderbuffers(1, &frameBufferDepthID);
//    glBindRenderbuffer(GL_RENDERBUFFER, frameBufferDepthID);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, frameBufferDepthID);

    glCreateTextures(GL_TEXTURE_2D, 1, &frameBufferDepthID);
    glBindTexture(GL_TEXTURE_2D, frameBufferDepthID);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width, width);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, frameBufferDepthID, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
//    ImGuiIO& io = ImGui::GetIO();
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

void clearRender() {
    glViewport(0, 0, width, height);
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imguiPreRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void imguiPostRender(ImGuiIO& io) {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
}

void sceneRender(Scene& scene) {
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glViewport(0, 0, scene.width, scene.height);
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene.draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::Begin("Scene");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    opened = ImGui::IsWindowFocused();
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