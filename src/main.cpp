#include "Framework/framework.h"
#include "resources.h"
#include <glm/vec3.hpp>

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_GLContext context;
    setupSDL(window, context);

    setupOpenGL();

    setupImGui(window, context);

    ShaderProgram shaderProgram(
        RESOURCE::SHADER::VERTEX_SHADER,
        RESOURCE::SHADER::FRAGMENT_SHADER
    );

    Model duckModel = Model::load<AssimpLoader>(RESOURCE::MODEL::DUCK, shaderProgram);
    SceneObject duck = duckModel;

    Scene scene(width, height);
    scene.addSceneObject(duck);

    float prevX = (float)width / 2;
    float prevY = (float)height / 2;

    auto timeAtLastFrame = std::chrono::system_clock::now();

    float boost = 0.0f;
    float cameraMovementSpeed = 0.05f;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiWindowFlags_NoDocking ;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    float duckPosition[3] = { 0.0f, 0.0f, 0.0f };
    float duckRotation[3] = { 0.0f, 0.0f, 0.0f };
    float duckScale[3] = { 1.0f, 1.0f, 1.0f };

    bool middleButtonDown = false;
    bool first = true;
    bool isRunning = true;
    while (isRunning) {
        auto timeAtThisFrame = std::chrono::system_clock::now();
        std::chrono::duration<float> seconds = timeAtThisFrame - timeAtLastFrame;
        float dt = seconds.count();
        timeAtLastFrame = timeAtThisFrame;

        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        if (opened) {
            if (state[SDL_SCANCODE_W]) {
                scene.camera.move(FORTH, cameraMovementSpeed + boost);
            }
            if (state[SDL_SCANCODE_A]) {
                scene.camera.move(LEFT, cameraMovementSpeed + boost);
            }
            if (state[SDL_SCANCODE_S]) {
                scene.camera.move(BACK, cameraMovementSpeed + boost);
            }
            if (state[SDL_SCANCODE_D]) {
                scene.camera.move(RIGHT, cameraMovementSpeed + boost);
            }
            if (state[SDL_SCANCODE_E]) {
                scene.camera.position.y += (0.05f + boost);
                //scene.camera.refresh();
            }
            if (state[SDL_SCANCODE_Q]) {
                scene.camera.position.y -= (0.05f + boost);
                //scene.camera.refresh();
            }
            if (state[SDL_SCANCODE_LSHIFT]) {
                if (cameraMovementSpeed + boost < 0.5) {
                    boost += 0.01f;
                }
            } else boost = 0.0f;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                isRunning = false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                isRunning = false;

            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    SDL_GetWindowSize(window, &width, &height);
                    scene.resize();

                    glDeleteFramebuffers(GL_FRAMEBUFFER, &FBO);
                    glDeleteTextures(1, &frameBufferTextureID);
                    glDeleteTextures(1, &frameBufferDepthID);
                    frameBufferTextureID = 0;
                    frameBufferDepthID = 0;

                    glGenFramebuffers(1, &FBO);
                    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

                    glGenTextures(1, &frameBufferTextureID);
                    glBindTexture(GL_TEXTURE_2D, frameBufferTextureID);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scene.width, scene.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameBufferTextureID, 0);

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
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_MIDDLE) {
                    middleButtonDown = true;
                    first = true;
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_MIDDLE) {
                    middleButtonDown = false;
                    first = false;
                }
            }

            if (event.type == SDL_MOUSEMOTION) {
                if (middleButtonDown) {
                    if(opened) {
                        auto x = (float) event.motion.x;
                        auto y = (float) event.motion.y;

                        if (first) {
                            prevX = x;
                            prevY = y;
                            first = false;
                        }

                        float offsetX = x - prevX;
                        float offsetY = prevY - y;

                        float mouseSensitivity = 5.0f;
                        offsetX *= mouseSensitivity;
                        offsetY *= mouseSensitivity;

                        scene.camera.rotate(offsetX * dt, offsetY * dt);

                        prevX = x;
                        prevY = y;
                    }
                }
            }
        }

        imguiPreRender();
        ImGui::DockSpaceOverViewport();

        if(ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("New"))
                {
                    //Do something
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        {
            ImGui::Begin("Models");
            ImGui::LoadingBar("Loading");
            ImGui::Text("x, y, z");
            ImGui::DragFloat3(" Position", duckPosition, 0.2f);
            ImGui::DragFloat3(" Rotation", duckRotation, 0.2f);
            ImGui::DragFloat3(" Scale", duckScale, 0.2f);

            duck.moveTo(glm::vec3(duckPosition[0], duckPosition[2], duckPosition[1]));

            duck.rotate(glm::radians(duckRotation[0] - 90), glm::vec3(1, 0, 0));
            duck.rotate(glm::radians(duckRotation[2]), glm::vec3(0, 0, 1));
            duck.rotate(glm::radians(duckRotation[1]), glm::vec3(0, 1, 0));

            duck.scale(glm::vec3(duckScale[0], duckScale[2], duckScale[1]));

            ImGui::Text("");
            ImGui::End();
        }

        {
            ImGui::Begin("Project");
            ImGui::End();
        }

        {
            ImGui::Begin("Inspector");
            ImGui::End();
        }

        glViewport(0, 0, width, height);
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        sceneRender(scene);

        scene.update();
        scene.draw();

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

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
