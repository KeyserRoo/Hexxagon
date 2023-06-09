#ifndef HEXXAGON_GAMEMANAGER_H
#define HEXXAGON_GAMEMANAGER_H

#include "SFML/Graphics.hpp"
#include "GamePanel.h"
#include "MenuPanel.h"
#include "PauseMenu.h"

class GameManager {
public:

    GameManager();

    virtual ~GameManager();

    void run();

    void update();

    void updateDeltaTime();

    void render();

    void eventListener();

    std::stack<Panel *> panels;
private:
    sf::RenderWindow *window;
    sf::Event event;
    sf::Clock deltaTimeClock;
    float deltaTime;

    void initializeWindow();

    void initializePanels();
};


#endif //HEXXAGON_GAMEMANAGER_H