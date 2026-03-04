#ifndef SPACE_HPP
#define SPACE_HPP

#include <vector>
#include "astro.hpp"

class Space
{
private:
    std::vector<Astro> astros;

    void drawGrid(float size, int divisions) const;

public:
    Space() = default;

    void addAstro(const Astro& a);

    void update(float dt);
    void draw(float gridSize = 60.0f, int gridDivisions = 120) const;

    const std::vector<Astro>& getAstros() const;
};

#endif