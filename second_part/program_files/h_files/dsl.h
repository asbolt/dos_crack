#ifndef DSL_H_
#define DSL_H_


#define CREATE_SPRITE(name, position_height)                                                                                    \
    sf::Sprite name##_sprite;                                                                                                   \
    sf::Vector2u name##_size = name##_texture.getSize();                                                                        \
    Sprite name##_sprite_configs = {{WINDOW_WIDTH/2, position_height},                                                          \
                                    {(float)(name##_size.x/2), (float)(name##_size.y/2)},                                       \
                                    {(float)(name##_NEEDED_SIZE_X/name##_size.x), (float)(name##_NEEDED_SIZE_Y/cat_size.y)}};   \
    sprite_ctor (name##_sprite, name##_texture, name##_sprite_configs);

#define CREATE_TEXTURE(name)                                                                                                    \
    sf::Texture name##_texture;                                                                                                 \
    texture_ctor (name##_texture, name##_TEXTURE_FILE_NAME);

#define LOAD_MUSIC(name)                                                                                                        \
    sf::Music name;                                                                                                             \
    name.openFromFile(name##_FILE_NAME);

#define LOAD_FONT(name)                                                                                                         \
    sf::Font name;                                                                                                              \
    name.loadFromFile(name##_FILE_NAME);

#define CREATE_TEXT(name, string, position_height)                                                                              \
    sf::Text name##_text;                                                                                                       \
    Text name##_text_config = {sf::Color::Black, string, position_height, FONT_LINE_SIZE};                                      \
    text_ctor (name##_text, font, name##_text_config);

#define CREATE_RECTANGLE(name)                                                                                                  \
    sf::RectangleShape name;                                                                                                    \
    Rectangle name##_config = {sf::Color::Black,                                                                                \
                               {name##_POSITION_X, name##_POSITION_Y},                                                          \
                               {name##_START_SIZE_X, name##_START_SIZE_Y}};                                                     \
    rectangle_ctor (name, name##_config);

#define CREATE_WINDOW(name)                                                                                                     \
    sf::RenderWindow name;                                                                                                      \
    window_ctor (name, WINDOW_WIDTH, WINDOW_HEIGHT, "Crack");


#endif