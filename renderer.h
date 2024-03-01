//
// Created by mason on 2/23/2024.
//

#ifndef INC_2D_FLUID_SIMULATION_RENDERER_H
#define INC_2D_FLUID_SIMULATION_RENDERER_H

#include "solver.h"

class Renderer {
public:
    explicit Renderer(sf::RenderTarget& target) :m_target{target} {}

    void render(const Solver& solver) const {
        // loop through all objects within the solver and draw them based on their properties

        sf::CircleShape circle{10.0f};
        circle.setOrigin(1.0f,1.0f);

        const auto& particles = solver.getParticles();
        for (auto& particle : particles) {
            circle.setPosition(particle.position);
            circle.setScale(1, 1);
            circle.setFillColor(sf::Color::White);
            m_target.draw(circle);
        }
    }

private:
    sf::RenderTarget& m_target;
};

#endif //INC_2D_FLUID_SIMULATION_RENDERER_H
