#include "../headerFiles/Button.h"

Button::Button(std::string text, sf::Font *font, sf::Vector2f size, sf::Vector2f pos, sf::Color idleColor,
               sf::Color hoverColor, sf::Color actionColor) {
    isPressed = false;

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->actionColor = actionColor;

    buttonBody.setSize(size);
    buttonBody.setPosition(pos);
    buttonBody.setOutlineThickness(10);
    buttonBody.setOutlineColor(sf::Color::Black);
    buttonBody.setFillColor(idleColor);

    buttonText.setFont(*font);
    buttonText.setString(text);
    buttonText.setOutlineThickness(3);
    buttonText.setOutlineColor(sf::Color::Black);
    buttonText.setCharacterSize(50);
    buttonText.setPosition(
            pos.x + buttonBody.getSize().x / 2.f - buttonText.getGlobalBounds().width / 2.f,
            pos.y + buttonBody.getSize().y / 2.f - buttonText.getGlobalBounds().height / 2.f - 7
    );
}

Button::Button(sf::Vector2f scale, sf::Vector2f position, sf::Texture* texture) {
    isPressed = false;

    this->buttonSprite.setTexture(*texture);
    buttonSprite.setOrigin(50,50);
    buttonSprite.setScale(scale);
    buttonSprite.setPosition(position);
    buttonBody.setOrigin(50,50);
    buttonBody.setSize({100, 100});
    buttonBody.setPosition(position);
}

void Button::update(const sf::Vector2f mousePosition) {
    buttonState = ButtonState::idle;
    isPressed = false;

    if (buttonBody.getGlobalBounds().contains(mousePosition)) {
        buttonState = ButtonState::hover;
        buttonSprite.rotate(1);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            buttonState = ButtonState::action;
            isPressed = true;
        }
    }
    switch (buttonState) {
        case ButtonState::idle:
            buttonBody.setFillColor(idleColor);
            break;
        case ButtonState::hover:
            buttonBody.setFillColor(hoverColor);
            break;
        case ButtonState::action:
            buttonBody.setFillColor(actionColor);
            break;
    }
}

void Button::renderTextButton(sf::RenderTarget *target) {
    target->draw(buttonBody);
    target->draw(buttonText);
}

void Button::renderImageButton(sf::RenderTarget *target) {
    target->draw(buttonSprite);
}