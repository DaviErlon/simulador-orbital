#ifndef PLANET_HPP
#define PLANET_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <vector>

class Astro
{
private:
    float pos[3];
    float vel[3];
    float acc[3];

    float mass;
    float radius;
    float color[3];

    static GLUquadric *quad;

public:
    Astro(float x, float y, float z,
          float vx, float vy, float vz,
          float r, float m,
          const float c[3]);

    static void init();
    static void destroy();

    void applyGravity(const Astro &other, float G);
    void update(float dt);
    void draw() const;

    float getX() const { return pos[0]; }
    float getY() const { return pos[1]; }
    float getZ() const { return pos[2]; }

    float getMass() const { return mass; }
    float getRadius() const { return radius; }
};

#endif