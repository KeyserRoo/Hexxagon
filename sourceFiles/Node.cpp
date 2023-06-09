#include "../headerFiles/Node.h"
#include "cmath"

Node::Node(Owner owner, std::pair<int, int> index) {
    this->team = owner;
    this->index = index;
    this->isPressed = false;

    const float x_pos = 650 + index.first * sqrt((9.f / 4.f * pow((radius + outline), 2)));
    const float y_pos = 0 + (index.first % 2 == 0 ? 0 : ((radius + outline) * sqrt(3) / 2)) +
                        index.second * (radius + outline) * sqrt(3) + index.first / 2 * 97.f;

    hex = new sf::CircleShape(radius, 6);
    jump = new sf::CircleShape(radius, 6);
    copy = new sf::CircleShape(radius, 6);

    elementInitializer(hex, x_pos, y_pos);
    elementInitializer(jump, x_pos, y_pos);
    elementInitializer(copy, x_pos, y_pos);

    switch (team) {
        case Owner::None:
            hex->setFillColor(setColorNone());
            break;
        case Owner::Red:
            hex->setFillColor(setColorRed());
            break;
        case Owner::Blue:
            hex->setFillColor(setColorBlue());
            break;
        case Owner::Nothing:
            hex->setFillColor(sf::Color::Black);
    }
    jump->setFillColor(sf::Color(209, 175, 23, 50));
    copy->setFillColor(sf::Color(209, 175, 23, 150));
}

Node::~Node() {
    delete hex;
    delete copy;
    delete jump;
}


void Node::setTeam(Owner owner) {
    this->team = owner;
}

Owner Node::getTeam() {
    return this->team;
}

int Node::getIndex() {
    return index.first * 9 + index.second;
}

bool Node::getPressed() {
    return isPressed;
}

void Node::setPressed(bool press) {
    isPressed = press;
}

sf::CircleShape Node::getJump() {
    return *jump;
}

sf::CircleShape Node::getCopy() {
    return *copy;
}

sf::CircleShape Node::getHex() {
    return *hex;
}


void Node::update(sf::Vector2f mousePosition) {
    setPressed(false);
    if (isInsideHex(mousePosition)) {
        setPressed(true);
    }
}

void Node::updateTeam() {
    switch (team) {
        case Owner::None:
            hex->setFillColor(setColorNone());
            break;
        case Owner::Red:
            hex->setFillColor(setColorRed());
            break;
        case Owner::Blue:
            hex->setFillColor(setColorBlue());
            break;
        case Owner::Nothing:
            hex->setFillColor(sf::Color::Black);
    }
}


void Node::renderHex(sf::RenderTarget *target) {
    target->draw(getHex());
}

void Node::renderJump(sf::RenderTarget *target) {
    target->draw(getJump());
}

void Node::renderCopy(sf::RenderTarget *target) {
    target->draw(getCopy());
}


bool Node::isInsideHex(sf::Vector2f mousePosition) {
    for (int i = 0; i < getHex().getPointCount(); i++) {
        sf::Vector2f current = getHex().getTransform().transformPoint(getHex().getPoint(i));
        sf::Vector2f next = getHex().getTransform().transformPoint(getHex().getPoint((i + 1) % 6));
        float crossProduct =
                (next.x - current.x) * (mousePosition.y - current.y) -
                (next.y - current.y) * (mousePosition.x - current.x);
        if (crossProduct < 0) return false;
    }
    return true;
}

void Node::elementInitializer(sf::CircleShape *element, float x_pos, float y_pos) {
    element->setOrigin(radius + outline / 2.f, radius + outline / 2.f);
    element->rotate(30);
    if (team != Owner::Nothing)
        element->setOutlineColor(sf::Color(100, 100, 100));
    else element->setOutlineColor(sf::Color::Black);
    element->setOutlineThickness(outline);
    element->setPosition(x_pos, y_pos);
}


sf::Color Node::setColorNone() {
    return {35, 117, 35};
}

sf::Color Node::setColorRed() {
    return {117, 35, 35};
}

sf::Color Node::setColorBlue() {
    return {35, 35, 117};
}