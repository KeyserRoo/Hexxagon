#ifndef HEXX_BOARD_H
#define HEXX_BOARD_H

#include "Node.h"

class Board {
public:
    Board();

    ~Board();

    std::vector<Node *> getFields();


    void renderNeighbours(sf::RenderTarget *target);


    Owner playerMoves(sf::Vector2f mousePositionView, Owner player);

    void checkNeighbours(Node *node);

    void setlastClicked(Node *last);

    void noMovesCheck();

private:
    Board(const Board &);

    Board &operator=(const Board &);

    Node *lastClicked;
    std::vector<Node *> blocksToCopyTo;
    std::vector<Node *> blocksToJumpTo;

    std::vector<Node *> fields = {};


    void initializeFields();

    void initializeNeighbours();


    void convertNeighbours(Node *node, Owner player);

    void nodeCopy(Node *node, Owner player);

    void nodeJump(Node *node, Owner player);
};

#endif //HEXX_BOARD_H
