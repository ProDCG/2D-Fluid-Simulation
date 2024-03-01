//
// Created by mason on 2/23/2024.
//

#ifndef INC_2D_FLUID_SIMULATION_SOLVER_H
#define INC_2D_FLUID_SIMULATION_SOLVER_H

#include <SFML/Graphics.hpp>

#include <cmath>
#include <vector>
#include <iostream>

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color = sf::Color::White;
    float density;

    Particle() = default;
    Particle(sf::Vector2f position_, float density_)
    :position{position_}, density{density_} {}



    [[nodiscard]]
    sf::Vector2f getPosition() const {
        return position;
    }

    [[nodiscard]]
    sf::Vector2f getVelocity() const {
        return velocity;
    }

    [[nodiscard]]
    float getDensity() const {
        return density;
    }
};

class Solver {
public:
    Solver() = default;

private:
    sf::Vector2f s_gravity = {0.0, 1000.0f};

    std::vector<Particle> s_particles;
    float s_frame_dt = 0.0f;
    float s_time = 0.0f;
    uint32_t s_substeps = 8;

};

#endif //INC_2D_FLUID_SIMULATION_SOLVER_H
