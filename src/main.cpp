#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Logger/Logger.h"
#include "renderer/ShaderProgram.h"
#include "resources/ResourceManager.h"
#include "renderer/texture2D/Texture2D.h"


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

GLfloat points[] = {
        .0f, .5f, .0f,
        .5f, -.5f, .0f,
        -.5f, -.5f, .0f
};

GLfloat colors[] = {
        1.f, .0f, .0f,
        0.f, 1.f, .0f,
        .0f, .0f, 1.f,
};

GLfloat texCords[] = {
        .5f, 1.f,
        1.f, .0f,
        .0f, .0f,
};

int main(int argc, char** argv) {
    auto& logger = Logger::getInstance();
    logger.subscribe(Logger::Subscriber("Engine", 0x5, 0xB, true));


    if (!glfwInit()) {
        logger.fatal("glfwInit() failed!");
        return -1;
    }

    logger.success("glfwInit()");

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
        logger.fatal("glfwCreateWindow(w,h,m,s) failed!");

        glfwTerminate();
        return -1;
    }

    logger.success("glfwCreateWindow(w,h,m,s)");

    glfwSetWindowSizeCallback(pWindow, glfwWindowResizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL()) {
        logger.fatal("gladLoadGL() failed!");
        return -1;
    }

    logger.success("gladLoadGL()");
    logger.info(std::string("Renderer ") + reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    logger.message(std::string("OpenGL version ") + reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    logger.message("OpenGL " + std::to_string(GLVersion.major) + "." + std::to_string(GLVersion.minor));

    glClearColor(1, 1, 0, 1);

    {
        ResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader",
                                                                 "res/shaders/vertex.txt",
                                                                 "res/shaders/fragment.txt");

        if(!pDefaultShaderProgram){
            logger.fatal("Can't create shader program DefaultShader");
            return -1;
        }

        auto texture = resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");

        logger.info("Created shader program DefaultShader");

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint texCords_vbo = 0;
        glGenBuffers(1, &texCords_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCords_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCords), texCords, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCords_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);

        while (!glfwWindowShouldClose(pWindow)) {

            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            texture->bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(pWindow);

            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}