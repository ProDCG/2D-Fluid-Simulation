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
    float radius;
    float gravity = 1000.0f;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color = sf::Color::White;

    Particle() = default;
    explicit Particle(sf::Vector2f position_)
    :position{position_}, velocity{sf::Vector2f(0.0f,0.0f)}, radius{1.0f} {}
    Particle(sf::Vector2f position_, sf::Vector2f velocity_)
    :position{position_}, velocity{velocity_}, radius{1.0f} {}
    Particle(sf::Vector2f position_, sf::Vector2f velocity_, float radius_)
    :position{position_}, velocity{velocity_}, radius{radius_} {}

    void update(float dt) {
        velocity += sf::Vector2f(0.0f, 1.0f) * gravity * dt;
        position += velocity * dt;
    }

    [[nodiscard]]
    float getRadius() const {
        return radius;
    }
};

class Solver {
public:
    Solver() = default;

    void update(float dt) {
        dt = 1.0/60.0;
        for (auto& particle : s_particles) particle.update(dt); // update all the particles
        checkCollisions();
    }

    [[nodiscard]]
    std::vector<Particle> getParticles() const {
        return s_particles;
    }

    Particle& addParticle(sf::Vector2f position, sf::Vector2f velocity, float radius) {
        s_particles.emplace_back(position, velocity, radius);
        return s_particles.back();
    }

private:
    float s_bounds_radius = 100.0f;
    sf::Vector2f s_origin;

    std::vector<Particle> s_particles;
    float s_coll_damp_factor = 0.5;

    void checkCollisions() {
        s_origin = sf::Vector2f(0, 0);
        for (auto& particle : s_particles) {
            sf::Vector2f p_displacement = particle.position - s_origin;
            float mag = std::sqrt(std::pow(p_displacement.x, 2) + std::pow(p_displacement.y, 2));
            if (mag + particle.getRadius() / 2.0f > s_bounds_radius) {
                p_displacement /= mag;

                float dotProduct = particle.velocity.x * p_displacement.x + particle.velocity.y * p_displacement.y;

                particle.velocity -= 2.0f * dotProduct * p_displacement;
                particle.velocity *= s_coll_damp_factor;

                particle.position = p_displacement * s_bounds_radius;
            }
        }
    }
};

#endif //INC_2D_FLUID_SIMULATION_SOLVER_H
