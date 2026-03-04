#include <GLFW/glfw3.h>
#include <iostream>
#include "main.hpp"
#include "camera.hpp"
#include "astro.hpp"
#include "colors.hpp"
#include "space.hpp"

const float WIDTH = 800.0f;
const float HEIGHT = 600.0f;

int main()
{
    // Inicializar GLFW e criar janela e câmera
    GLFWwindow *window = StartGLFW();
    Camera cam = Camera(25.0f);

    // conectar ponteiro da janela à câmera para controle de zoom
    glfwSetWindowUserPointer(window, &cam);
    glfwSetScrollCallback(window, scrollCallback);

    // Inicializar recursos dos astros
    Astro::init();

    // Criar o espaço e popular com astros
    Space space = Space();
    populateSpace(&space);
    
    // loop principal
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        // Processar teclas para movimentar a câmera ou fechar a janela
        cam.processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Configurar a visão da câmera
        resize(window);
        cam.applyView();

        // Atualizar e desenhar o espaço
        float dt = getDeltaTime();
        
        space.update(dt);
        space.draw();
        
        glfwSwapBuffers(window);
    }

    Astro::destroy();
    glfwTerminate();
    return 0;
}

void populateSpace(Space *space)
{
    // ======== Dois astros massivos ========
    float mass1 = 300.0f;
    float mass2 = 300.0f;
 
    // Distância inicial entre eles
    float dist = 8.0f;

    // Velocidades para órbita circular
    float v1 = std::sqrt(mass2 * mass2 / (dist * (mass1 + mass2)));
    float v2 = std::sqrt(mass1 * mass1 / (dist * (mass1 + mass2)));

    float x1 = -dist * mass2 / (mass1 + mass2);
    float x2 = dist * mass1 / (mass1 + mass2);

    space->addAstro(Astro{
        x1, 0.0f, 0.0f, // posição (centro de massa)
        0.0f, 0.0f, v1,                              // velocidade
        1.0f,                                        // raio
        mass1,                                       // massa
        amarelo});

    space->addAstro(Astro{
        x2, 0.0f, .0f,
        0.0f, 0.0f, -v2,
        1.0f,
        mass2,
        azul});

}

GLFWwindow *StartGLFW()
{
    if (!glfwInit())
    {
        std::cerr << "Erro na inicialização!" << std::endl;
        return nullptr;
    }

    GLFWwindow *window = glfwCreateWindow(
        WIDTH, HEIGHT,
        "Simulador de Orbita",
        NULL, NULL);
        
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return window;
}

void resize(GLFWwindow *window)
{
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    float aspect = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.1, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (cam)
        cam->zoom(static_cast<float>(yoffset));
}

float getDeltaTime()
{
    static float lastTime = glfwGetTime();

    float currentTime = glfwGetTime();
    float dt = currentTime - lastTime;
    lastTime = currentTime;

    return dt;
}