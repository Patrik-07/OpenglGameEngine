#include <iostream>
#include "framework/framework.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <chrono>

const char* vertexShaderPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\vertexShader01.glsl";
const char* fragmentShaderPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\fragmentShader01.glsl";

const char* imgPath01 = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\res\\img01.png";
const char* imgPath02 = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\res\\container.jpg";

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_GLContext context;
    setupSDL(window, context);

    setupOpenGL();

    setupImGui(window, context);

    ShaderProgram shaderProgram(vertexShaderPath, fragmentShaderPath);

//    Model hulkbusterModel = ModelLoader::load(R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\hulkbuster.obj)");
//    Model lightModel = ModelLoader::load(R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\light.fbx)");
//    Model bugattiModel = ModelLoader::load(R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\bugatti\bugatti.obj)");
    Model backpackModel = ModelLoader::load(R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\backpack\backpack.obj)");
    Model duckModel = ModelLoader::load(R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\duck\10602_Rubber_Duck_v1_L3.obj)");

//    SceneObject hulkbuster(hulkbusterModel, shaderProgram);
//    SceneObject light(lightModel, shaderProgram);
//    SceneObject bugatti(bugattiModel, shaderProgram);
    SceneObject backpack(backpackModel, shaderProgram);
    SceneObject duck(duckModel, shaderProgram);

//    hulkbuster.scale(glm::vec3(2.0f));
//    light.move(glm::vec3(0.0f, 20.0f, 0.0f));

    Scene scene;
//    scene.addSceneObject(hulkbuster);
//    scene.addSceneObject(light);
//    scene.addSceneObject(bugatti);
//    scene.addSceneObject(backpack);
    scene.addSceneObject(duck);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float prevX = (float)width / 2;
    float prevY = (float)height / 2;

    auto timeAtLastFrame = std::chrono::system_clock::now();

    float boost = 0.0f;
    float cameraMovementSpeed = 0.05f;


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL2_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
            scene.camera.refresh();
        }
        if (state[SDL_SCANCODE_Q]) {
            scene.camera.position.y -= (0.05f + boost);
            scene.camera.refresh();
        }
        if (state[SDL_SCANCODE_LSHIFT]) {
            if (cameraMovementSpeed + boost < 0.5) {
                boost += 0.01f;
            }
        } else boost = 0.0f;

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

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Duck properties");

            ImGui::DragFloat3("Position", duckPosition);
            ImGui::DragFloat3("Rotation", duckRotation, 5.0f);
            ImGui::DragFloat3("Scale", duckScale);

            duck.moveTo(glm::vec3(duckPosition[0], duckPosition[2], duckPosition[1]));

            duck.rotate(glm::radians(duckRotation[0]), glm::vec3(1, 0, 0));
            duck.rotate(glm::radians(duckRotation[2]), glm::vec3(0, 1, 0));
            duck.rotate(glm::radians(duckRotation[1]), glm::vec3(0, 0, 1));

            duck.scale(glm::vec3(duckScale[0], duckScale[2], duckScale[1]));

            ImGui::Text("");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        glViewport(0, 0, width, height);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.draw();
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


//        gridShader02.use();
//        gridShader02.setUniform("mvp.view", view);
//        gridShader02.setUniform("mvp.projection", projection);
//        gridShader02.setUniform("cameraPos", camera.getPosition());
//        glEnable(GL_DEPTH);
//        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
