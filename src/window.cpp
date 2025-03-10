#include <stdio.h>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "const_in_patch.h"
#include "window.h"

errors_in_patch draw_window ()
{
    uint x_size_window = 600;
    uint y_size_window = 600; 

	sf::RenderWindow window(sf::VideoMode({x_size_window, y_size_window}), "SFML works!");

    sf::Texture texture ("./pictures/sunset.png");

    int left   = 0; 
    int top    = 100;
    int width  = 800;
    int height = 600;

    sf::Vector2i position (left, top);
    sf::Vector2i size     (width, height);

    sf::IntRect rectSourceSprite(position, size);
    sf::Sprite sprite(texture, rectSourceSprite);

    sf::Clock clock;

    uint quantity_of_pictures_in_gif = 23; //24 - 1

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        if (clock.getElapsedTime().asSeconds() > 0.05f)
        {
            if (rectSourceSprite.position.x == int (quantity_of_pictures_in_gif * x_size_window))
            {
                rectSourceSprite.position.x = 0;
            }

            else
            {
                rectSourceSprite.position.x += x_size_window;
            }

            sprite.setTextureRect(rectSourceSprite);
            clock.restart();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

	return NOT_ERROR;
}