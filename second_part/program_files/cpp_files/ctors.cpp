#include "../h_files/ctors.h"

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

void window_ctor (sf::RenderWindow& window, float size_x, float size_y, const char* name)
{
    window.create (sf::VideoMode(size_x, size_y), name, sf::Style::Close);
}