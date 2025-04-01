#ifndef CTORS_H_
#define CTORS_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstring>

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

#define music_FILE_NAME "../../music/music.mp3"
#define cat_TEXTURE_FILE_NAME "../../images/cat.png"
#define loading_TEXTURE_FILE_NAME "../../images/loading.png"
#define font_FILE_NAME "../../fonts/font.ttf"

void texture_ctor (sf::Texture& herotexture, const char *texture_file_name);
void music_ctor (sf::Music& music, const char *music_file_name);
void sprite_ctor (sf::Sprite& sprite, sf::Texture& sprite_texture, struct Sprite sprite_configs);
void text_ctor (sf::Text& text, sf::Font& font, Text text_configs);
void rectangle_ctor (sf::RectangleShape& rectangle, Rectangle rectangle_config);
void window_ctor (sf::RenderWindow& window, float size_x, float size_y, const char* name);

#endif