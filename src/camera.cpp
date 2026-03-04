#include "camera.hpp"
#include <GL/glu.h>
#include <cmath>

Camera::Camera(float r)
    : theta(0.0f),
      phi(0.0f),
      radius(r),
      rotationSpeed(0.03f),
      zoomSpeed(2.0f),
      minRadius(1.0f),
      maxRadius(50.0f)
{
}

void Camera::applyView() const
{
    float camX = radius * cos(phi) * sin(theta);
    float camY = radius * sin(phi);
    float camZ = radius * cos(phi) * cos(theta);

    float upY = (cos(phi) >= 0.0f) ? 1.0f : -1.0f;

    gluLookAt(
        camX, camY, camZ,
        0.0f, 0.0f, 0.0f,
        0.0f, upY, 0.0f);
}

void Camera::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        theta -= rotationSpeed;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        theta += rotationSpeed;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        phi += rotationSpeed;

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        phi -= rotationSpeed;
}

void Camera::zoom(float offset)
{
    radius -= offset * zoomSpeed;

    if (radius < minRadius)
        radius = minRadius;

    if (radius > maxRadius)
        radius = maxRadius;
}