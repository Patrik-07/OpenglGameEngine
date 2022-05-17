#pragma once

#include "imgui/imgui.h"
#include "imgui/sdl_opengl3/imgui_impl_sdl.h"
#include "imgui/sdl_opengl3/imgui_impl_opengl3.h"

#include "SDL2/SDL.h"
#include "../Opengl/Buffer/FramerBuffer.h"
#include "../Scene/Scene.h"
#include "../Animation/Animator.h"

class ImGuiRenderer {
    ImGuiIO* io;
    FrameBuffer frameBuffer;
    FrameBuffer depthBuffer;
    FrameBuffer normalBuffer;
    FrameBuffer solidBuffer;
    ShaderProgram depthProgram;

public:
    ImGuiRenderer(SDL_Window*& window, SDL_GLContext& context) : depthProgram(RESOURCE::SHADER::DEPTH_VS, RESOURCE::SHADER::DEPTH_FS) {
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
        normalBuffer = FrameBuffer::create(w, h);
        solidBuffer = FrameBuffer::create(w, h);
        depthBuffer = FrameBuffer::create(1024, 1024);
    }

    void resize(int w, int h) {
        frameBuffer = FrameBuffer::create(w, h);
        normalBuffer = FrameBuffer::create(w, h);
        solidBuffer = FrameBuffer::create(w, h);
    }

    void preRender() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();
    }

    void sceneRender(Scene& scene, float deltaTime) {
        // Depth buffer
        glViewport(0, 0, 1024, 1024);
        glCullFace(GL_FRONT);
        depthBuffer.bind();

        float near_plane = 1.0f, far_plane = 7.5f;
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        glm::mat4 lightView = glm::lookAt(
                glm::vec3(-3.0f, 4.0f, -1.0f),
                glm::vec3(3.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        glm::mat4 v = scene.camera.viewMatrix;
        glm::mat4 p = scene.camera.projectionMatrix;

        scene.camera.viewMatrix = lightView;
        scene.camera.projectionMatrix = lightProjection;

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.update(deltaTime, false);
        scene.draw();

        scene.camera.viewMatrix = v;
        scene.camera.projectionMatrix = p;

        depthBuffer.unbind();
        glCullFace(GL_BACK);

        ImGui::Begin("Depth");
        ImVec2 pos2 = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddImage(
                (void*)depthBuffer.depthID,
                pos2,
                ImVec2(pos2.x + (float)scene.width/2, pos2.y + (float)scene.height/2),
                ImVec2(0, 1),
                ImVec2(1, 0)
        );
        ImGui::End();

        // Scene
        glViewport(0, 0, scene.width, scene.height);
        frameBuffer.bind();

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SceneObject* fox = scene.getSceneObject(0);
        ShaderProgram& foxShader = fox->getShader();
        scene.update(deltaTime, true);
        foxShader.setUniform("depthMap", depthBuffer.depthID, 1);
        foxShader.setUniform("lightSpaceMatrix", glm::value_ptr(lightSpaceMatrix));
        foxShader.setUniform("viewPos", glm::value_ptr(scene.camera.position), 3);
        foxShader.setUniform("lightPos", glm::value_ptr(glm::vec3(-3.0f, 4.0f, -1.0f)), 3);
        foxShader.setUniform("enableNormal", false);
        foxShader.setUniform("enableSolid", false);
        scene.draw();

        frameBuffer.unbind();

        ImGui::Begin("Scene");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        scene.hasFocus = ImGui::IsWindowFocused();
        ImVec2 pos1 = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddImage(
            (void*)frameBuffer.textureID,
            pos1,
            ImVec2(pos1.x + (float)scene.width, pos1.y + (float)scene.height),
            ImVec2(0, 1),
            ImVec2(1, 0)
        );
        ImGui::End();

        normalBuffer.bind();

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.update(deltaTime, true);
        foxShader.setUniform("depthMap", depthBuffer.depthID, 1);
        foxShader.setUniform("lightSpaceMatrix", glm::value_ptr(lightSpaceMatrix));
        foxShader.setUniform("viewPos", glm::value_ptr(scene.camera.position), 3);
        foxShader.setUniform("lightPos", glm::value_ptr(glm::vec3(-3.0f, 4.0f, -1.0f)), 3);
        foxShader.setUniform("enableNormal", true);
        foxShader.setUniform("enableSolid", false);
        scene.draw();

        normalBuffer.unbind();

        ImGui::Begin("Normal");
        ImVec2 pos3 = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddImage(
                (void*)normalBuffer.textureID,
                pos3,
                ImVec2(pos3.x + (float)scene.width, pos3.y + (float)scene.height),
                ImVec2(0, 1),
                ImVec2(1, 0)
        );
        ImGui::End();

        solidBuffer.bind();

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.update(deltaTime, true);
        foxShader.setUniform("depthMap", depthBuffer.depthID, 1);
        foxShader.setUniform("lightSpaceMatrix", glm::value_ptr(lightSpaceMatrix));
        foxShader.setUniform("viewPos", glm::value_ptr(scene.camera.position), 3);
        foxShader.setUniform("lightPos", glm::value_ptr(glm::vec3(-3.0f, 4.0f, -1.0f)), 3);
        foxShader.setUniform("enableNormal", false);
        foxShader.setUniform("enableSolid", true);
        scene.draw();

        solidBuffer.unbind();

        ImGui::Begin("Solid");
        ImVec2 pos4 = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddImage(
                (void*)solidBuffer.textureID,
                pos4,
                ImVec2(pos4.x + (float)scene.width, pos4.y + (float)scene.height),
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