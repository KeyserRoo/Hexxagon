#ifndef HEXXAGON_PANEL_H
#define HEXXAGON_PANEL_H

#include "stack"
#include "SFML/Graphics.hpp"

class Panel {
public:
    Panel(sf::RenderWindow *window, std::stack<Panel *> *panels);

    virtual ~Panel() = default;


    sf::RenderWindow *window;

    std::stack<Panel *> *panels;

    sf::Vector2f mousePositionView;

    bool ends = false;


    virtual void update(const float &deltaTime) = 0;

    virtual void updateInput(const float &deltaTime);

    virtual void updateMousePositions();


    virtual void render(sf::RenderTarget *target = nullptr) = 0;


    const bool &endPanel() const;

private:
};


#endif //HEXXAGON_PANEL_H