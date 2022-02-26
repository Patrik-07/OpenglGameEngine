#include <iostream>
#include "framework/framework.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <chrono>

const char* vertexShaderPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\vertexShader01.glsl";
const char* fragmentShaderPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\fragmentShader01.glsl";

const char* gridVSPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\gridVertexShader.glsl";
const char* gridFSPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\gridFragmentShader.glsl";

const char* gridVSPath02 = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\gridVertexShader02.glsl";
const char* gridFSPath02 = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\gridFragmentShader02.glsl";

const char* imgPath01 = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\res\\img01.png";
const char* imgPath02 = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\res\\container.jpg";

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_GLContext context;
    setupSDL(window, context);

    setupOpenGL();

    setupImGui(window, context);

    ShaderProgram shaderProgram(vertexShaderPath, fragmentShaderPath);
    ShaderProgram gridShader(gridVSPath, gridFSPath);
    ShaderProgram gridShader02(gridVSPath02, gridFSPath02);


    Texture t(R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\backpack\diffuse.jpg)", DIFFUSE);
    shaderProgram.setUniform("material.diffuseMap", t, 0);
    shaderProgram.setUniform("enableTexture", false);

    Model m = ModelLoader::load(R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\hulkbuster.obj)");
    Camera camera;

    Grid grid(5);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float prevX = (float)width / 2;
    float prevY = (float)height / 2;

    auto timeAtLastFrame = std::chrono::system_clock::now();

    float boost = 0.0f;

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
            camera.move(FORTH, boost);
        }
        if (state[SDL_SCANCODE_A]) {
            camera.move(LEFT, boost);
        }
        if (state[SDL_SCANCODE_S]) {
            camera.move(BACK, boost);
        }
        if (state[SDL_SCANCODE_D]) {
            camera.move(RIGHT, boost);
        }
        if (state[SDL_SCANCODE_LSHIFT]) {
            if (boost < 1.5f) {
                boost += 0.02f;
            }
        } else boost = 0.0f;


        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                isRunning = false;

            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    SDL_GetWindowSize(window, &width, &height);
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

                    camera.rotate(offsetX * dt, offsetY * dt);

                    prevX = x;
                    prevY = y;
                }
            }
        }

        glViewport(0, 0, width, height);
        glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(5.0f));
        glm::mat4 view  = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix();

        shaderProgram.use();
        shaderProgram.setUniform("mvp.model", model);
        shaderProgram.setUniform("mvp.view", view);
        shaderProgram.setUniform("mvp.projection", projection);

        m.draw(shaderProgram);

        model = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f));

//        gridShader02.use();
//        gridShader02.setUniform("mvp.view", view);
//        gridShader02.setUniform("mvp.projection", projection);
//        gridShader02.setUniform("cameraPos", camera.getPosition());
//        glEnable(GL_DEPTH);
//        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        gridShader.use();
        gridShader.setUniform("mvp.model", model);
        gridShader.setUniform("mvp.view", view);
        gridShader.setUniform("mvp.projection", projection);
        glm::vec3 cameraPosition = camera.getPosition();
        int y = (int)cameraPosition.y;
        if (y > 60) {
            grid.reset(4);
        } else if (y > 30) {
            grid.reset(6);
        } else grid.reset(10);
        gridShader.setUniform("cameraPosition", camera.getPosition());

        grid.draw();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
