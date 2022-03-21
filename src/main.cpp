#include "Framework/Framework.h"

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_GLContext context;
    ImGuiRenderer imGuiRenderer = init(window, context);

    ShaderProgram shaderProgram(
        RESOURCE::SHADER::DEFAULT_VS,
        RESOURCE::SHADER::DEFAULT_FS
    );

    // Load models
    Model rpg_character_model = Model::load<AssimpLoader>(RESOURCE::MODEL::RPG_CHARACTER, RESOURCE::MODEL::RPG_CHARACTER_BONES);
//    Model a = Model::load<AssimpLoader>(RESOURCE::MODEL::RPG_CHARACTER_BONES);

    SceneObject rpg_character(rpg_character_model, shaderProgram);
    rpg_character.scale(glm::vec3(0.02f, 0.02f, 0.02f));
    rpg_character.rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // Create camera
    Camera camera(shaderProgram);

    // Init scene
    Scene scene(width, height, camera);
    scene.addSceneObject(rpg_character);

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
            isRunning = processEvent(event);

            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    SDL_GetWindowSize(window, &width, &height);
                    scene.resize(width, height);
                    imGuiRenderer.resize(width, height);
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
