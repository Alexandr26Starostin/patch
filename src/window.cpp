#include <stdio.h>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "const_in_patch.h"
#include "hack_program.h"
#include "window.h"

errors_in_patch_t draw_window ()
{
    errors_in_patch_t status = NOT_ERROR;

    uint x_size_window = 600;
    uint y_size_window = 600; 

	sf::RenderWindow window(sf::VideoMode({x_size_window, y_size_window}), "Patch complites hacking!!!");

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

    // sf::Music music;

    //const char* name_file_with_music = "./music/titanic.mp3";

    // if (!music.openFromFile("./music/titanic.mp3"))
    // {
    //     printf ("\n\nError in %s:$d\n\nCan not open file with music on file %s\n", __FILE__, __LINE__, name_file_with_music);
    //     return CAN_NOT_OPEN_MUSIC_FILE;
    // }

    // music.play();

    status = hack_program ();
    if (status) {return status;}

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

   //music.pause();

	return status;
}