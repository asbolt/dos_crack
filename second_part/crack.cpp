#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <math.h>

void makeCrackFile ();
void a (sf::RenderWindow& window, sf::Text& text, sf::Sprite& herosprite);

int main ()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Close);

    sf::Music music;
    music.openFromFile("music.mp3");//загружаем фай
//воспроизводим музыку

    sf::Texture herotexture;
	herotexture.loadFromFile("cat.png");
    herotexture.setSmooth(true);
 
	sf::Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setPosition(400, 300);
    herosprite.setScale(0.4, 0.8);
    herosprite.setOrigin(75, 55);

    sf::Texture herotexture2;
	herotexture2.loadFromFile("log.png");
    herotexture2.setSmooth(true);
 //
	sf::Sprite herosprite2;
	herosprite2.setTexture(herotexture2);
	herosprite2.setPosition(200, 500);
    herosprite2.setScale(0.35, 0.35);

    sf::Clock clock; 

    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text text("Press enter to crack", font, 45);
    text.setFillColor(sf::Color::Black);
	text.setPosition(300, 500);

    sf::Text text2("Crack is done!", font, 45);
    text2.setFillColor(sf::Color::Black);
	text2.setPosition(350, 500);

    sf::Text text3("Loading...", font, 45);
    text3.setFillColor(sf::Color::Black);
	text3.setPosition(350, 445);

    a (window, text, herosprite);

    //herosprite.setPosition(400, 300);
    clock.restart();

    sf::RectangleShape rectangle (sf::Vector2f(120, 39));
        rectangle.setFillColor (sf::Color::Black);
        rectangle.setPosition (210, 506);
    while (window.isOpen() && clock.getElapsedTime().asSeconds() < 5.5)
    {
        float time = clock.getElapsedTime().asSeconds();
        rectangle.setSize(sf::Vector2f(120 + time*50, 39));
        
        window.clear(sf::Color::White);
	    window.draw(herosprite);
        window.draw(herosprite2);
        window.draw(rectangle);
        window.draw(text3);
	    window.display();
    }

    music.play();
    clock.restart();
    makeCrackFile ();
    while (window.isOpen())
    {
        music.setLoop(true); 
        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();
        time = time/8000;

        sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

                if (event.type == sf::Event::KeyPressed)
                    if (event.key.code == sf::Keyboard::Enter) 
                        window.close();

		}

        float   x = herosprite.getPosition().x,
                y = herosprite.getPosition().y;

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        float dX = pixelPos.x - x;
	    float dY = pixelPos.y - y;
        float rotation = (atan2(dY, dX)) * 180 / 3.14159265;
		herosprite.setRotation(rotation);

        float   dx2 = 0,
                dy2 = 0;


        if (abs(dX) > 10) dx2 = cos (rotation * 3.1415 / 180) * 3* time;
        if (abs(dY) > 10) dy2 = sin (rotation * 3.1415 / 180) * 3 * time;
        herosprite.setPosition (x + dx2, y + dy2);

        window.clear(sf::Color::White);
	    window.draw(herosprite);
        window.draw(text2);
	    window.display();
    }
}

void a (sf::RenderWindow& window, sf::Text& text, sf::Sprite& herosprite)
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
	    window.draw(herosprite);
        window.draw(text);
	    window.display();

    }
}

void makeCrackFile ()
{
    FILE *com_file = fopen ("program.com", "rb");
    if (com_file == NULL)
        return;

    fseek (com_file, 0, SEEK_END);
    int file_size = ftell (com_file);
    fseek (com_file, 0, SEEK_SET);

    char *buffer = (char *)calloc (file_size, sizeof(char));
    if (buffer == NULL)
        return;
        
    fread (buffer, sizeof(char), file_size, com_file);

    fclose (com_file);

    FILE *crack_file = fopen ("hacked_program.com", "ab");
    fseek (crack_file, 0, SEEK_SET);
    int i = 0;

    while (i != file_size)
    {
        if (*(buffer + i) != 't')
        {
            fprintf (crack_file, "%c", *(buffer + i));
            i++;
        } else {
            fprintf (crack_file, "u");
            i++;
        }
    }

    fclose (crack_file);
    free (buffer);

    return;
}



