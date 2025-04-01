#include <iostream>
#include <sstream>
#include <math.h>
#include "../h_files/dsl.h"
#include "../h_files/ctors.h"
#include "../h_files/graphics.h"
#include "../h_files/crack.h"

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