#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <math.h>
#include "ctors.h"

const float LOADING_TIME = 4;
const float GAME_SPEED = 8000;
const float CAT_SPEED = 3;

void start_screen (sf::RenderWindow& window, sf::Text& text, sf::Sprite& cat_cprite);
void loading_screen (sf::RenderWindow& window, sf::Clock& clock, sf::RectangleShape& rectangle, \
                     sf::Sprite& cat_sprite, sf::Sprite& loading_sprite, sf::Text text);
void end_screen (sf::RenderWindow& window, sf::Sprite& cat_sprite, sf::Clock& clock, sf::Music& music, sf::Text& text);

#endif