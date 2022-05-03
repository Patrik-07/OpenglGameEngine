#include "framework/Framework.h"
#include "framework/animation/Animation.h"
#include "framework/animation/Animator.h"

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_GLContext context;
    ImGuiRenderer imGuiRenderer = init(window, context);

    ShaderProgram shaderProgram(
        RESOURCE::SHADER::DEFAULT_VS,
        RESOURCE::SHADER::DEFAULT_FS
    );

    /*
        modelLoader modelLoader = AssimpLoader()
        AnimatedModel m;
        modelLoader.loadAnimated(RESOURCE::MODEL::FOX);
    */

    // Load models
    // change this to: modelLoader.load()
    AssimpLoader modelLoader = AssimpLoader();
    Model model = modelLoader.load(RESOURCE::MODEL::FOX);

    Animation animation(RESOURCE::MODEL::FOX, &model);

    Animator animator(animation);

    SceneObject object(model, shaderProgram);
    object.scale(glm::vec3(0.05f, 0.05f, 0.05f));

    // Create camera
    Camera camera(shaderProgram);

    // Init scene
    Scene scene(width, height, camera);
    scene.addSceneObject(object);

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

        animator.updateAnimation(deltaTime);
        imGuiRenderer.sceneRender(scene, animator, shaderProgram);
        imGuiRenderer.postRender();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
