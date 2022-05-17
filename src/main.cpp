#include "framework/Framework.h"
#include "framework/animation/Animation.h"

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_GLContext context;
    ImGuiRenderer imGuiRenderer = init(window, context);

    ShaderProgram shaderProgram(
        RESOURCE::SHADER::DEFAULT_VS,
        RESOURCE::SHADER::DEFAULT_FS
    );

    AssimpLoader modelLoader = AssimpLoader();

    // Plane
    Model planeModel = modelLoader.load(RESOURCE::MODEL::PLANE);
    SceneObject plane(planeModel, shaderProgram);
    plane.translate(glm::vec3(0.0f, -0.025f, 0.0f));
    plane.scale(glm::vec3(15.0f, 15.0f, 15.0f));

    // Fox
    Model foxModel = modelLoader.load(RESOURCE::MODEL::FOX);
    Animation animation(RESOURCE::MODEL::FOX, &foxModel);
    SceneObject fox(foxModel, shaderProgram);
    fox.translate(glm::vec3(0.0f, 0.825f, 0.0f));
    fox.scale(glm::vec3(0.025f, 0.025f, 0.025f));
    fox.setCurrentAnimation(animation);

    // Camera
    Camera camera(shaderProgram);

    // Init scene
    Scene scene(width, height, camera);
    scene.addSceneObject(fox);
    scene.addSceneObject(plane);

    Timer timer;
    CameraHandler cameraHandler(camera);
    float positions[3] = { 0.0f,  0.825f, 0.0f };
    float tempPos[3] = {0.0f};

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

        imGuiRenderer.sceneRender(scene, deltaTime);
        imGuiRenderer.postRender();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
