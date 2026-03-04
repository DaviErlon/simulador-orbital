#include "astro.hpp"
#include "colors.hpp"
#include <vector>

GLUquadric *Astro::quad = nullptr;

Astro::Astro(float x, float y, float z,
             float vx, float vy, float vz,
             float r, float m,
             const float c[3])
{
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    vel[0] = vx;
    vel[1] = vy;
    vel[2] = vz;
    acc[0] = acc[1] = acc[2] = 0.0f;

    radius = r;
    mass = m;

    color[0] = c[0];
    color[1] = c[1];
    color[2] = c[2];
}

void Astro::init()
{
    quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
}

void Astro::destroy()
{
    gluDeleteQuadric(quad);
}

void Astro::applyGravity(const Astro &other, float G)
{
    float dx = other.pos[0] - pos[0];
    float dy = other.pos[1] - pos[1];
    float dz = other.pos[2] - pos[2];

    float distSq = dx * dx + dy * dy + dz * dz;
    float dist = std::sqrt(distSq);

    if (dist < 0.001f)
        return;

    float force = G * mass * other.mass / distSq;

    acc[0] += force * dx / (dist * mass);
    acc[1] += force * dy / (dist * mass);
    acc[2] += force * dz / (dist * mass);
}

void Astro::update(float dt)
{
    vel[0] += acc[0] * dt;
    vel[1] += acc[1] * dt;
    vel[2] += acc[2] * dt;

    pos[0] += vel[0] * dt;
    pos[1] += vel[1] * dt;
    pos[2] += vel[2] * dt;

    acc[0] = acc[1] = acc[2] = 0.0f;
}

void Astro::draw() const
{
    if (!quad)
        return;

    glPushMatrix();

    glTranslatef(pos[0], pos[1], pos[2]);
    glColor3fv(color);

    gluSphere(quad, radius, 40, 40);

    glPopMatrix();
}