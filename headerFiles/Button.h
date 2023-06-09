#ifndef HEXXAGON_BUTTON_H
#define HEXXAGON_BUTTON_H

#include "SFML/Graphics.hpp"
#include <string>

enum class ButtonState{
    idle,
    hover,
    action
};

class Button {
public:
    Button(std::string text, sf::Font *font, sf::Vector2f size, sf::Vector2f pos, sf::Color idleColor,
           sf::Color hoverColor, sf::Color actionColor);

    Button(sf::Vector2f scale, sf::Vector2f position, sf::Texture* texture);

    sf::Sprite buttonSprite;
    sf::RectangleShape buttonBody;
    sf::Text buttonText;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color actionColor;

    ButtonState buttonState;
    bool isPressed;

    void update(sf::Vector2f mousePosition);

    void renderTextButton(sf::RenderTarget *target);

    void renderImageButton(sf::RenderTarget *target);
};


#endif //HEXXAGON_BUTTON_H
