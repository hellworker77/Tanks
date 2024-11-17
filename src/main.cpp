#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Logger/Logger.h"

int g_windowWidth = 640;
int g_windowHeight = 480;

void glfwWindowResizeCallback(GLFWwindow* pWindow, int width, int height){
    g_windowWidth = width;
    g_windowHeight = height;
    glViewport(0, 0, g_windowWidth, g_windowHeight);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void) {
    auto *logger = new Logger();
    logger->subscribe({
                              "ENGINE", 13, 5, 11, true
                      });

    if (!glfwInit()) {
        logger->error("glfwInit() failed!");
        delete logger;
        return -1;
    }

    logger->print("glfwInit() success");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *pWindow;

    pWindow = glfwCreateWindow(g_windowWidth,
                               g_windowHeight,
                               "Hello World",
                               nullptr,
                               nullptr);
    if (!pWindow) {
        logger->error("glfwCreateWindow(w,h,m,s) failed!");

        glfwTerminate();
        delete logger;
        return -1;
    }

    logger->print("glfwCreateWindow(w,h,m,s) success");

    glfwSetWindowSizeCallback(pWindow, glfwWindowResizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL()) {
        logger->error("gladLoadGL() failed!");

        delete logger;
        return -1;
    }
    logger->print("gladLoadGL() success");

    logger->print(std::string("Renderer ") + reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    logger->print(std::string("OpenGL version ") + reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    logger->print("OpenGL " + std::to_string(GLVersion.major) + "." + std::to_string(GLVersion.minor));

    glClearColor(1, 1, 0, 1);

    while (!glfwWindowShouldClose(pWindow)) {

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    delete logger;
    return 0;
}