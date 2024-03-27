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

        sf::CircleShape circle{1.0f};
        circle.setOrigin(0.0f,0.0f);

        sf::Vector2f windowOffset = sf::Vector2f(1000.0f / 2.0f, 1000 / 2.0f);

        const auto& particles = solver.getParticles();
        for (auto& particle : particles) {
            circle.setRadius(particle.getRadius());
            circle.setPosition(particle.position + windowOffset);
            circle.setScale(1, 1);
            circle.setFillColor(sf::Color::White);
            m_target.draw(circle);
        }

        circle.setPosition(windowOffset - sf::Vector2f(100, 100));
        circle.setScale(1, 1);
        circle.setRadius(101);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(3);
        m_target.draw(circle);
    }

private:
    sf::RenderTarget& m_target;
};

#endif //INC_2D_FLUID_SIMULATION_RENDERER_H
