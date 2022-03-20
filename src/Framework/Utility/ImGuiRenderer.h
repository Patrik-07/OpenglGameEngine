#pragma once

#include "imgui/imgui.h"
#include "imgui/sdl_opengl3/imgui_impl_sdl.h"
#include "imgui/sdl_opengl3/imgui_impl_opengl3.h"

#include "SDL2/SDL.h"
#include "../Opengl/Buffer/FramerBuffer.h"
#include "../Scene/Scene.h"

class ImGuiRenderer {
    ImGuiIO* io;
    FrameBuffer frameBuffer;

public:
    ImGuiRenderer(SDL_Window*& window, SDL_GLContext& context) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io = &ImGui::GetIO();
        io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io->ConfigFlags |= ImGuiWindowFlags_NoDocking;

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplSDL2_InitForOpenGL(window, context);
        ImGui_ImplOpenGL3_Init("#version 330 core");

        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        frameBuffer = FrameBuffer::create(w, h);
    }

    void resize(int w, int h) {
        frameBuffer = FrameBuffer::create(w, h);
    }

    void preRender() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();
    }

    void sceneRender(Scene& scene) {
        frameBuffer.bind();

        glViewport(0, 0, scene.width, scene.height);
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.update();
        scene.draw();

        frameBuffer.unbind();

        ImGui::Begin("Scene");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        scene.hasFocus = ImGui::IsWindowFocused();
        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddImage(
            (void*)frameBuffer.textureID,
            pos,
            ImVec2(pos.x + (float)scene.width, pos.y + (float)scene.height),
            ImVec2(0, 1),
            ImVec2(1, 0)
        );
        ImGui::End();
    }

    void postRender() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }
    }
};