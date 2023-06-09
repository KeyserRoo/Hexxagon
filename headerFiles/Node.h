#ifndef HEXX_NODE_H
#define HEXX_NODE_H

#include "Owner.h"
#include <utility>
#include "SFML/Graphics.hpp"

class Node {
public:
    Node(Owner owner, std::pair<int, int> index);

    ~Node();


    std::vector<Node *> oneTileNeighbours;
    std::vector<Node *> twoTileNeighbours;


    void setTeam(Owner owner);

    Owner getTeam();

    int getIndex();

    void setPressed(bool press);

    bool getPressed();


    void update(sf::Vector2f mousePosition);

    void updateTeam();


    void renderHex(sf::RenderTarget *target);

    void renderJump(sf::RenderTarget *target);

    void renderCopy(sf::RenderTarget *target);


    static sf::Color setColorNone();

    static sf::Color setColorRed();

    static sf::Color setColorBlue();
private:
    Owner team;

    std::pair<int, int> index;

    bool isPressed;
    float radius = 50.f;

    float outline = 5.f;

    sf::CircleShape *hex;
    sf::CircleShape *jump;
    sf::CircleShape *copy;

    sf::CircleShape getJump();

    sf::CircleShape getCopy();

    sf::CircleShape getHex();


    bool isInsideHex(sf::Vector2f mousePosition);


    void elementInitializer(sf::CircleShape *element, float x_pos, float y_pos);
};

#endif //HEXX_NODE_H
