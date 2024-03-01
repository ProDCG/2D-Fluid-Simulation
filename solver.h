//
// Created by mason on 2/23/2024.
//

#ifndef INC_2D_FLUID_SIMULATION_SOLVER_H
#define INC_2D_FLUID_SIMULATION_SOLVER_H

#include <SFML/Graphics.hpp>

#include <cmath>
#include <vector>
#include <iostream>

template <typename T> int signum(T val) { return (T(0) < val) - (val < T(0)); }


struct Particle {
    float radius = 1.0f;
    float gravity = 10.0f;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color = sf::Color::White;

    Particle() = default;
    explicit Particle(sf::Vector2f position_)
    :position{position_}, velocity{sf::Vector2f(0.0f,0.0f)} {}
    Particle(sf::Vector2f position_, sf::Vector2f velocity_)
    :position{position_}, velocity{velocity_} {}

    void update(float dt) {
        velocity += sf::Vector2f(0.0f, 1.0f) * gravity * dt;
        position += velocity * dt;
    }
};

class Solver {
public:
    Solver() = default;

    void update(float dt) {
        for (auto& particle : s_particles) particle.update(dt); // update all the particles
        checkCollisions();
    }

    [[nodiscard]]
    std::vector<Particle> getParticles() const {
        return s_particles;
    }

    Particle& addParticle(sf::Vector2f position, sf::Vector2f velocity) {
        s_particles.emplace_back(position, velocity);
        return s_particles.back();
    }

private:
    sf::Vector2f s_bounds = {200, 200};

    std::vector<Particle> s_particles;
    float s_coll_damp_factor = 0.5;

    void checkCollisions() {
        for (auto& particle : s_particles) {
            if (std::abs(particle.position.x) > s_bounds.x) {
                particle.position.x = s_bounds.x * ((float)signum(particle.position.x));
                particle.velocity.x *= -1 * s_coll_damp_factor;
            } else if (std::abs(particle.position.y) > s_bounds.y) {
                particle.position.y = s_bounds.y * ((float)signum(particle.position.y));
                particle.velocity.y *= -1 * s_coll_damp_factor;
            }
        }
    }
};

#endif //INC_2D_FLUID_SIMULATION_SOLVER_H
