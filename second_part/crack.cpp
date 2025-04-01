#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <cstring>
#include <math.h>

#define CREATE_SPRITE(name, position_height)  sf::Sprite name##_sprite;                                                                                             \
                             sf::Vector2u name##_size = name##_texture.getSize();                                                                  \
                             Sprite name##_sprite_configs = {{WINDOW_WIDTH/2, position_height},                                                    \
                                                             {(float)(name##_size.x/2), (float)(name##_size.y/2)},                                 \
                                                             {(float)(name##_NEEDED_SIZE_X/name##_size.x), (float)(name##_NEEDED_SIZE_Y/cat_size.y)}}; \
                             sprite_ctor (name##_sprite, name##_texture, name##_sprite_configs);

#define CREATE_TEXTURE(name) sf::Texture name##_texture;                                                                                           \
                             texture_ctor (name##_texture, name##_TEXTURE_FILE_NAME);

#define LOAD_MUSIC(name)     sf::Music name;                                                                                                       \
                             name.openFromFile(name##_FILE_NAME);

#define LOAD_FONT(name)      sf::Font name;                                                                                                        \
                             name.loadFromFile(name##_FILE_NAME);

#define CREATE_TEXT(name, string, position_height)    \
                             sf::Text name##_text; \
                             Text name##_text_config = {sf::Color::Black, string, position_height, FONT_LINE_SIZE}; \
                             text_ctor (name##_text, font, name##_text_config);

#define CREATE_RECTANGLE(name) sf::RectangleShape name; \
                                Rectangle name##_config = {sf::Color::Black, \
                                                              {name##_POSITION_X, name##_POSITION_Y}, \
                                                              {name##_START_SIZE_X, name##_START_SIZE_Y}};\
                                rectangle_ctor (name, name##_config);

#define CREATE_WINDOW(name) \
        sf::RenderWindow name (sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Crack", sf::Style::Close);


struct Sprite
{
    sf::Vector2f position;
    sf::Vector2f center;
    sf::Vector2f extension;
};

struct Text
{
    const sf::Color&   color;
    const char         *string;
    float              position_height;
    float              line_spasing;
};

struct Rectangle
{
    const sf::Color&   color;
    sf::Vector2f position;
    sf::Vector2f size;
};


const float WINDOW_WIDTH  = 800;
const float WINDOW_HEIGHT = 600;
const float cat_NEEDED_SIZE_X = 90, cat_NEEDED_SIZE_Y = 90;
const float loading_NEEDED_SIZE_X = 400, loading_NEEDED_SIZE_Y = 38;
const float LOADING_POSITION_HEIGHT = 526;
const float ONE_LETTER_SIZE = 10;
const float FONT_LINE_SIZE = 45;
const float FIRST_TEXT_POSITION_HEIGHT = 500;
const float SECOND_TEXT_POSITION_HEIGHT = 445;
const float THIRD_TEXT_POSITION_HEIGHT = 500;
const float rectangle_POSITION_X = 210, rectangle_POSITION_Y = 506;
const float RECTANGLE_NEEDED_SIZE_X = 355;
const float rectangle_START_SIZE_X = 30, rectangle_START_SIZE_Y = 39;
const float LOADING_TIME = 4;
const float GAME_SPEED = 8000;
const float CAT_SPEED = 3;

const char *music_FILE_NAME = "music/music.mp3";
const char *cat_TEXTURE_FILE_NAME = "images/cat.png";
const char *loading_TEXTURE_FILE_NAME = "images/loading.png";
const char *font_FILE_NAME = "fonts/font.ttf";
const char *PROGRAM_TO_CRACK = "programs/program.com";
const char *CRACKED_PROGRAM = "programs/hacked_program.com";


void makeCrackFile ();
void start_screen (sf::RenderWindow& window, sf::Text& text, sf::Sprite& cat_cprite);
void loading_screen (sf::RenderWindow& window, sf::Clock& clock, sf::RectangleShape& rectangle, \
                     sf::Sprite& cat_sprite, sf::Sprite& loading_sprite, sf::Text text);
void end_screen (sf::RenderWindow& window, sf::Sprite& cat_sprite, sf::Clock& clock, sf::Music& music, sf::Text& text);
void texture_ctor (sf::Texture& herotexture, const char *texture_file_name);
void music_ctor (sf::Music& music, const char *music_file_name);
void sprite_ctor (sf::Sprite& sprite, sf::Texture& sprite_texture, struct Sprite sprite_configs);
void text_ctor (sf::Text& text, sf::Font& font, Text text_configs);
void rectangle_ctor (sf::RectangleShape& rectangle, Rectangle rectangle_config);

int main ()
{

    CREATE_WINDOW (window);

    LOAD_MUSIC (music);

    CREATE_TEXTURE (cat);
	CREATE_SPRITE (cat, WINDOW_HEIGHT/2);

    CREATE_TEXTURE (loading);
	CREATE_SPRITE (loading, LOADING_POSITION_HEIGHT); 

    LOAD_FONT (font);
    CREATE_TEXT (first, "Press enter to crack", FIRST_TEXT_POSITION_HEIGHT);
    CREATE_TEXT (second, "Loading...", SECOND_TEXT_POSITION_HEIGHT);
    CREATE_TEXT (third, "Crack completed!", THIRD_TEXT_POSITION_HEIGHT);

    CREATE_RECTANGLE (rectangle);

    start_screen (window, first_text, cat_sprite);

    sf::Clock clock;
    loading_screen (window, clock, rectangle, cat_sprite, loading_sprite, second_text);

    music.play();
    clock.restart();
    makeCrackFile ();
    end_screen (window, cat_sprite, clock, music, third_text);

    return 0;
}

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

void makeCrackFile ()
{
    FILE *com_file = fopen (PROGRAM_TO_CRACK, "rb");
    if (com_file == NULL)
        return;

    fseek (com_file, 0, SEEK_END);
    int file_size = ftell (com_file);
    fseek (com_file, 0, SEEK_SET);

    char *buffer = (char *)calloc (file_size, sizeof(char));
    if (buffer == NULL)
    {
        fclose (com_file);
        return;
    }
        
    fread (buffer, sizeof(char), file_size, com_file);
    fclose (com_file);

    FILE *crack_file = fopen (CRACKED_PROGRAM, "ab");
    fseek (crack_file, 0, SEEK_SET);
    int i = 0;

    while (i != file_size)
    {
        if (*(buffer + i) != 't')                       // 't' == JE
        {
            fprintf (crack_file, "%c", *(buffer + i));
            i++;
        } else {
            fprintf (crack_file, "u");                  // 'u' == JNE
            i++;
        }
    }

    fclose (crack_file);
    free (buffer);

    return;
}

void texture_ctor (sf::Texture& herotexture, const char *texture_file_name)
{
	herotexture.loadFromFile(texture_file_name);
    herotexture.setSmooth(true);
}

void sprite_ctor (sf::Sprite& sprite, sf::Texture& sprite_texture, struct Sprite sprite_configs)
{
    sprite.setTexture(sprite_texture);
	sprite.setPosition(sprite_configs.position);
    sprite.setScale(sprite_configs.extension);
    sprite.setOrigin(sprite_configs.center);
}

void text_ctor (sf::Text& text, sf::Font& font, Text text_configs)
{
    text.setString (text_configs.string);
    text.setFont (font);
    text.setFillColor (text_configs.color);
    text.setCharacterSize (text_configs.line_spasing);
	text.setPosition((WINDOW_WIDTH - strlen (text_configs.string) * ONE_LETTER_SIZE) / 2, text_configs.position_height);
}

void rectangle_ctor (sf::RectangleShape& rectangle, Rectangle rectangle_config)
{
    rectangle.setFillColor (rectangle_config.color);
    rectangle.setPosition (rectangle_config.position);
    rectangle.setSize (rectangle_config.size);
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



