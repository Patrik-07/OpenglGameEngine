#include <iostream>
#include "framework/framework.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective

const char* vertexShaderPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\vertexShader01.glsl";
const char* fragmentShaderPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\fragmentShader01.glsl";

const char* gridVSPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\gridVertexShader.glsl";
const char* gridFSPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\gridFragmentShader.glsl";

const char* imgPath01 = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\res\\img01.png";
const char* imgPath02 = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\res\\container.jpg";

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_GLContext context;
    setupSDL(window, context);

    setupOpenGL();

    setupImGui(window, context);

    //    ShaderProgram shaderProgram(vertexShaderPath, fragmentShaderPath);
    ShaderProgram gridShader(gridVSPath, gridFSPath);

//    Texture t(R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\backpack\diffuse.jpg)", DIFFUSE);
//    shaderProgram.setUniform("material.diffuseMap", t, 0);
//    shaderProgram.setUniform("enableTexture", false);
//
//    Model m = ModelLoader::load(R"(C:\Users\PatrikSanta\Prog\C++\Imgui\src\models\donut.obj)");
//    Camera camera;

    Grid grid;

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    SDL_GetWindowSize(window, &width, &height);
                }
            }
//            if (event.type == SDL_KEYDOWN) {
//                switch (event.key.keysym.sym) {
//                    case SDLK_UP: camera.move(FORTH); break;
//                    case SDLK_DOWN: camera.move(BACK); break;
//                    case SDLK_RIGHT: camera.move(RIGHT); break;
//                    case SDLK_LEFT: camera.move(LEFT); break;
//                }
//            }
        }

        glViewport(0, 0, width, height);
        glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(1.0f, 1.0f, 0.0f));
//        glm::mat4 view  = camera.getViewMatrix();
//        glm::mat4 projection = camera.getProjectionMatrix();

//        shaderProgram.use();
//        shaderProgram.setUniform("mvp.model", model);
//        shaderProgram.setUniform("mvp.view", view);
//        shaderProgram.setUniform("mvp.projection", projection);
//
//        m.draw(shaderProgram);

        unsigned int VAO;
        float v[] {
            1.0f, 0.0f, 0.0f,
            -1.0f, 0.0f, 0.0f
        };

        unsigned int i[] {
            0, 1
        };

        glGenVertexArrays(1, &VAO);

        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), v, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(unsigned int), i, GL_STATIC_DRAW);

        glBindVertexArray(0);

        gridShader.use();
        gridShader.setUniform("w", 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
