#include <iostream>
#include "../headerFiles/GameManager.h"

GameManager::GameManager() {
    initializeWindow();
    initializePanels();
}

GameManager::~GameManager() {
    delete this->window;
    while (!panels.empty()) {
        delete this->panels.top();
        this->panels.pop();
    }
}

void GameManager::initializeWindow() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    this->window = new sf::RenderWindow(sf::VideoMode({1920, 1080}), "Countragon", sf::Style::Default, settings);
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);
}

void GameManager::initializePanels() {
    panels.push(new MenuPanel(this->window, &this->panels));
}

void GameManager::run() {
    while (window->isOpen()) {
        updateDeltaTime();
        update();
        render();
    }
}

void GameManager::update() {
    if (!panels.empty()) {
        eventListener();
        panels.top()->update(deltaTime);
        if (panels.top()->endPanel()) {
            delete panels.top();
            panels.pop();
        }
    } else {
        window->close();
    }
}

void GameManager::updateDeltaTime() {
    deltaTime = deltaTimeClock.getElapsedTime().asSeconds();
}

void GameManager::render() {
    window->clear();
    if (!panels.empty())
        panels.top()->render(window);
    window->display();
}

void GameManager::eventListener() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            panels.top()->updateInput(deltaTime);
        }
    }
}