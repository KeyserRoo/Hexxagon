#include <iostream>
#include "../headerFiles//GameManager.h"


PauseMenu::PauseMenu(sf::RenderWindow &window) {
    initializeButtons(&window);
    initializeBackground(window);
}

PauseMenu::~PauseMenu() {
    delete resume;
    delete quit;
}

void PauseMenu::update(const sf::Vector2f &mousePositionView) {
    resume->update(mousePositionView);
    quit->update(mousePositionView);
}

void PauseMenu::render(sf::RenderTarget &target) {
    target.draw(background);
    resume->renderTextButton(&target);
    quit->renderTextButton(&target);
}

void PauseMenu::initializeBackground(sf::RenderWindow &window) {
    this->background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    this->background.setFillColor(sf::Color(30, 30, 30, 100));
}

void PauseMenu::initializeButtons(sf::RenderWindow *window) {
    sf::Vector2f size(600.f, 120.f);
    float buttonPositionX = window->getSize().x / 2 - 300.f;
    float buttonPositionY = (window->getSize().y / 2) - 250.f;
    std::string fontLocation = "..\\resourceFiles\\arial.ttf";
    if (!font.loadFromFile(fontLocation)) {
        std::cout << "Could not load font from " << fontLocation;
    }
    resume = new Button("RESUME", &font, size,
                        sf::Vector2f(buttonPositionX, buttonPositionY),
                        Node::setColorRed(),
                        Node::setColorNone(),
                        Node::setColorBlue());

    quit = new Button("QUIT", &font, size,
                      sf::Vector2f(buttonPositionX, buttonPositionY * 2),
                      Node::setColorRed(),
                      Node::setColorNone(),
                      Node::setColorBlue());
}