#ifndef HEXXAGON_PAUSEMENU_H
#define HEXXAGON_PAUSEMENU_H

#include "SFML/Graphics.hpp"
#include "Panel.h"
#include "Button.h"

class PauseMenu {
public:
    explicit PauseMenu(sf::RenderWindow &window);

    ~PauseMenu();


    Button *resume;
    Button *quit;


    void update(const sf::Vector2f &mousePositionView);


    void render(sf::RenderTarget &target);


    void initializeBackground(sf::RenderWindow &window);

    void initializeButtons(sf::RenderWindow *window);

private:
    sf::Font font;
    sf::RectangleShape background;
};


#endif //HEXXAGON_PAUSEMENU_H
