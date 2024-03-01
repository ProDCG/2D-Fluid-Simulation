#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "renderer.h"
#include "solver.h"

int main()
{
    constexpr int32_t window_width = 1000;
    constexpr int32_t window_height = 1000;
    const uint32_t frame_rate = 60;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Liquid Simulation", sf::Style::Default, settings);
    window.setFramerateLimit(frame_rate);

    Solver solver;
    Renderer renderer(window);

    Particle particle = solver.addParticle(sf::Vector2f(100.0f,100.0f), sf::Vector2f(100.0f,0.0f));
//    particle.setVelocity(sf::Vector2f(10, 10));

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // terminate the window
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        solver.update(clock.restart().asSeconds());
        window.clear(sf::Color::Black);
        renderer.render(solver);
        window.display();
    }


    std::cout << "here" << std::endl;
}