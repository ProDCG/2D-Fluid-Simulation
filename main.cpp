#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

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

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // terminate the window
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        solver.update();
        window.clear(sf::Color::Black);
        renderer.render(solver);
        window.display();
    }


    std::cout << "here" << std::endl;
}