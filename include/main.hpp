#ifndef MAIN_HPP
#define MAIN_HPP

#include "GLFW/glfw3.h"
#include "space.hpp"

GLFWwindow* StartGLFW(void);
void resize(GLFWwindow *window);
void populateSpace(Space* space);
float getDeltaTime();
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

#endif
