#include <GLFW/glfw3.h>
#include <iostream>
#include "main.hpp"

const float WIDTH = 800.0f;
const float HEIGHT = 600.0f;

int main()
{
    GLFWwindow* window = StartGLFW();

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
    }


    glfwTerminate();
    return 0;
}

GLFWwindow* StartGLFW(){
    if(!glfwInit()){
        std::cerr << "Erro na inicialização!" << std::endl;
        return nullptr;
    }
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Simulador de Orbita", NULL, NULL);
    glfwMakeContextCurrent(window);
    glClearColor(0.0,0.0,0.0,1.0);

    return window; 
}