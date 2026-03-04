#include "space.hpp"
#include "colors.hpp"

#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <cmath>

void Space::addAstro(const Astro& a)
{
    astros.push_back(a);
}

void Space::update(float dt)
{
    const float G = 1.0f;

    for (size_t i = 0; i < astros.size(); i++)
    {
        for (size_t j = 0; j < astros.size(); j++)
        {
            if (i == j) continue;
            astros[i].applyGravity(astros[j], G);
        }
    }

    for (auto& a : astros)
        a.update(dt);
}

void Space::draw(float gridSize, int gridDivisions) const
{
    for (const auto& a : astros)
        a.draw();

    drawGrid(gridSize, gridDivisions);
}

const std::vector<Astro>& Space::getAstros() const
{
    return astros;
}

void Space::drawGrid(float size, int un) const
{
    float d = size / 2.0f;
    float spc = size / un;

    const float G = 1.0f;
    const float scale = 0.05f;

    // Softening real (aumente para mais suavidade)
    const float softening = 2.0f;
    const float soft2 = softening * softening;

    glLineWidth(0.8f);
    glColor3fv(branco);

    for (int i = 0; i <= un; i++)
    {
        float pos = -d + i * spc;

        for (int j = 0; j < un; j++)
        {
            float z1 = -d + j * spc;
            float z2 = -d + (j + 1) * spc;

            float y1 = 0.0f;
            float y2 = 0.0f;

            for (const auto& s : astros)
            {
                float dx1 = pos - s.getX();
                float dz1 = z1 - s.getZ();
                float dx2 = pos - s.getX();
                float dz2 = z2 - s.getZ();

                float r1 = std::sqrt(dx1*dx1 + dz1*dz1 + soft2);
                float r2 = std::sqrt(dx2*dx2 + dz2*dz2 + soft2);

                y1 -= scale * (G * s.getMass()) / r1;
                y2 -= scale * (G * s.getMass()) / r2;
            }

            glBegin(GL_LINES);
            glVertex3f(pos, y1, z1);
            glVertex3f(pos, y2, z2);
            glEnd();
        }

        for (int j = 0; j < un; j++)
        {
            float x1 = -d + j * spc;
            float x2 = -d + (j + 1) * spc;

            float y1 = 0.0f;
            float y2 = 0.0f;

            for (const auto& s : astros)
            {
                float dx1 = x1 - s.getX();
                float dz1 = pos - s.getZ();
                float dx2 = x2 - s.getX();
                float dz2 = pos - s.getZ();

                float r1 = std::sqrt(dx1*dx1 + dz1*dz1 + soft2);
                float r2 = std::sqrt(dx2*dx2 + dz2*dz2 + soft2);

                y1 -= scale * (G * s.getMass()) / r1;
                y2 -= scale * (G * s.getMass()) / r2;
            }

            glBegin(GL_LINES);
            glVertex3f(x1, y1, pos);
            glVertex3f(x2, y2, pos);
            glEnd();
        }
    }
}