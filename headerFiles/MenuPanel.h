#ifndef HEXXAGON_MENUPANEL_H
#define HEXXAGON_MENUPANEL_H

#include "SFML/Graphics.hpp"
#include "Panel.h"
#include "Button.h"

class MenuPanel : public Panel {
public:
    explicit MenuPanel(sf::RenderWindow *window, std::stack<Panel *> *states);

    ~MenuPanel();


    void update(const float &deltaTime) override;


    void render(sf::RenderTarget *target = nullptr) override;


    void initializeBackground(sf::RenderWindow *window);

    void initializeButtons(sf::RenderWindow *window);

private:
    sf::Texture *menuBG;
    sf::RectangleShape background;

    sf::Font font;

    Button *newGame;
    Button *quit;
};


#endif //HEXXAGON_MENUPANEL_H