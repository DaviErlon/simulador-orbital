#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GLFW/glfw3.h>

class Camera
{
private:
    float theta;
    float phi;
    float radius;

    float rotationSpeed;
    float zoomSpeed;

    float minRadius;
    float maxRadius;

public:
    Camera(float r = 15.0f);

    void applyView() const;
    void processInput(GLFWwindow* window);
    void zoom(float offset);
};

#endif