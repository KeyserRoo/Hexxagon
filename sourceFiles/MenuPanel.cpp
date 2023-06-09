#include <iostream>
#include "../headerFiles//GameManager.h"

MenuPanel::MenuPanel(sf::RenderWindow *window, std::stack<Panel *> *states) : Panel(window, states) {
    initializeBackground(window);
    initializeButtons(window);
}

MenuPanel::~MenuPanel() {
    delete newGame;
    delete quit;
    delete menuBG;
}

void MenuPanel::update(const float &deltaTime) {
    Panel::updateMousePositions();
    updateInput(deltaTime);

    newGame->update(mousePositionView);
    quit->update(mousePositionView);

    if (newGame->isPressed) {
        panels->push(new GamePanel(this->window, this->panels));
    }
    if (quit->isPressed) {
        ends = true;
    }
}

void MenuPanel::render(sf::RenderTarget *target) {
    target->draw(background);
    newGame->renderTextButton(target);
    quit->renderTextButton(target);
}

void MenuPanel::initializeButtons(sf::RenderWindow *window) {
    sf::Vector2f size(600.f, 150.f);
    float buttonPositionX = (window->getSize().x / 2) - 300.f;
    float buttonPositionY = (window->getSize().y / 2) - 75.f;
    std::string fontLocation = "..\\resourceFiles\\arial.ttf";
    if (!font.loadFromFile(fontLocation)) {
        std::cout << "Could not load font from " << fontLocation;
    }
    newGame = new Button("NEW GAME", &font, size,
                         sf::Vector2f(buttonPositionX, buttonPositionY * 0.75f),
                         Node::setColorRed(),
                         Node::setColorNone(),
                         Node::setColorBlue());
    quit = new Button("QUIT", &font, size,
                      sf::Vector2f(buttonPositionX, buttonPositionY * 1.25),
                      Node::setColorRed(),
                      Node::setColorNone(),
                      Node::setColorBlue());
}

void MenuPanel::initializeBackground(sf::RenderWindow *window) {
    menuBG = new sf::Texture();
    if (!menuBG->loadFromFile("..\\resourceFiles\\Menubg.png")) {
        std::cout << "ooo, nie zaladowalo sie";
    }
    background.setSize(sf::Vector2f(window->getSize()));
    background.setPosition(sf::Vector2f(0, 0));
    background.setTexture(menuBG);
}