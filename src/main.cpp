#include "Framework/framework.h"
#include "resources.h"
#include "Framework/Utility/Timer.h"
#include "Framework/Utility/CameraHandler.h"
#include "Framework/Utility/ImGuiRenderer.h"
#include <glm/vec3.hpp>

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_GLContext context;
    ImGuiRenderer imGuiRenderer = init(window, context);

    ShaderProgram shaderProgram(
        RESOURCE::SHADER::VERTEX_SHADER,
        RESOURCE::SHADER::FRAGMENT_SHADER
    );

    // Load models
    Model duckModel = Model::load<AssimpLoader>(RESOURCE::MODEL::DUCK);
    SceneObject duck(duckModel, shaderProgram);
    duck.rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // Create camera
    Camera camera(shaderProgram);

    // Init scene
    Scene scene(width, height, camera);
    scene.addSceneObject(duck);

    Timer timer;
    CameraHandler cameraHandler(camera);

    bool isRunning = true;
    while (isRunning) {
        float deltaTime = timer.getDeltaTime();

        if (scene.hasFocus) {
            cameraHandler.process(deltaTime);
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
                    scene.resize(width, height);
                    imGuiRenderer.resize(scene.width, scene.height);
                }
            }
        }

        imGuiRenderer.preRender();

        // add ImGui commands here
        // ...

        imGuiRenderer.sceneRender(scene);
        imGuiRenderer.postRender();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
