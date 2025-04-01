#include "../h_files/graphics.h"

void start_screen (sf::RenderWindow& window, sf::Text& text, sf::Sprite& cat_sprite)
{

    while (window.isOpen())
    {
        sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Enter) return;

		}

        window.clear(sf::Color::White);
	    window.draw(cat_sprite);
        window.draw(text);
	    window.display();

    }
}

void loading_screen (sf::RenderWindow& window, sf::Clock& clock, sf::RectangleShape& rectangle, \
                     sf::Sprite& cat_sprite, sf::Sprite& loading_sprite, sf::Text text)
{
    float time = clock.getElapsedTime().asSeconds();

    while (window.isOpen() && time < LOADING_TIME)
    {
        time = clock.getElapsedTime().asSeconds();
        rectangle.setSize(sf::Vector2f(rectangle_START_SIZE_X + time * RECTANGLE_NEEDED_SIZE_X / LOADING_TIME, \
                                       rectangle_START_SIZE_Y));
        
        window.clear(sf::Color::White);
	    window.draw(cat_sprite);
        window.draw(loading_sprite);
        window.draw(rectangle);
        window.draw(text);
	    window.display();
    }
}

void end_screen (sf::RenderWindow& window, sf::Sprite& cat_sprite, sf::Clock& clock, sf::Music& music, sf::Text& text)
{
    while (window.isOpen())
    {
        music.setLoop(true); 
        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();
        time = time/GAME_SPEED;

        sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

                if (event.type == sf::Event::KeyPressed)
                    if (event.key.code == sf::Keyboard::Enter) 
                        window.close();

		}

        float   x = cat_sprite.getPosition().x,
                y = cat_sprite.getPosition().y;

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        float dX = pixelPos.x - x;
	    float dY = pixelPos.y - y;
        float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
		cat_sprite.setRotation(rotation);

        float   dx2 = 0,
                dy2 = 0;


        if (abs(dX) > 10) dx2 = cos (rotation * 3.1415 / 180) * CAT_SPEED * time;
        if (abs(dY) > 10) dy2 = sin (rotation * 3.1415 / 180) * CAT_SPEED * time;
        cat_sprite.setPosition (x + dx2, y + dy2);

        window.clear(sf::Color::White);
	    window.draw(cat_sprite);
        window.draw(text);
	    window.display();
    }
}