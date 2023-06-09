#include "../headerFiles/Panel.h"

Panel::Panel(sf::RenderWindow *window,std::stack<Panel*>* panels) {
    this->window = window;
    this->panels = panels;
}

const bool &Panel::endPanel() const {
    return ends;
}

void Panel::updateMousePositions() {
    mousePositionView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void Panel::updateInput(const float &deltaTime) {

}
