#include "../headerFiles/Board.h"

Board::Board() {
    initializeFields();
    initializeNeighbours();
    lastClicked = nullptr;
}

Board::~Board() {
    for (Node *hexagon: fields) {
        delete hexagon;
    }
}


std::vector<Node *> Board::getFields() {
    return fields;
}


void Board::renderNeighbours(sf::RenderTarget *target) {
    for (Node *node: blocksToCopyTo) {
        node->renderCopy(target);
    }
    for (Node *node: blocksToJumpTo) {
        node->renderJump(target);
    }
}


void Board::initializeFields() {
    for (int i = 0; i < 81; ++i) {
        int sum = (i % 9) + ((i - (i % 9)) / 9);
        if (sum > 3 && sum < 13)fields.push_back(new Node(Owner::None, std::pair<int,int>{(i - (i % 9)) / 9, i % 9}));
        else fields.push_back(new Node(Owner::Nothing, std::pair<int,int>{(i - (i % 9)) / 9, i % 9}));
    }
    fields[49]->setTeam(Owner::Nothing);
    fields[39]->setTeam(Owner::Nothing);
    fields[32]->setTeam(Owner::Nothing);
    fields[72]->setTeam(Owner::Red);
    fields[44]->setTeam(Owner::Red);
    fields[4]->setTeam(Owner::Red);
    fields[76]->setTeam(Owner::Blue);
    fields[36]->setTeam(Owner::Blue);
    fields[8]->setTeam(Owner::Blue);
}

void Board::initializeNeighbours() {
    std::vector<std::pair<int, int>> oneTileIndexing = {{0,  -1},
                                                        {1,  -1},
                                                        {1,  0},
                                                        {0,  1},
                                                        {-1, 1},
                                                        {-1, 0}};

    std::vector<std::pair<int, int>> twoTileIndexing = {{0,  -2},
                                                        {1,  -2},
                                                        {2,  -2},
                                                        {2,  -1},
                                                        {2,  0},
                                                        {1,  1},
                                                        {0,  2},
                                                        {-1, 2},
                                                        {-2, 2},
                                                        {-2, 1},
                                                        {-2, 0},
                                                        {-1, -1}};
    for (Node *hexagon: fields) {
        int nodeIndex = hexagon->getIndex();
        if (hexagon->getTeam() == Owner::Nothing) continue;
        for (int i = 0; i < 6; ++i) {
            int check = (nodeIndex + oneTileIndexing[i].first * 9 + oneTileIndexing[i].second);
            if (check < 0 || check > 80) continue;
            if (fields[check]->getTeam() == Owner::Nothing) continue;
            if (std::abs(hexagon->getIndex() % 9 - check % 9) > 3) continue;
            hexagon->oneTileNeighbours.push_back(fields[check]);
        }
        for (int i = 0; i < 12; ++i) {
            int check = (nodeIndex + twoTileIndexing[i].first * 9 + twoTileIndexing[i].second);
            if (check < 0 || check > 80) continue;
            if (fields[check]->getTeam() == Owner::Nothing)continue;
            if (std::abs(hexagon->getIndex() % 9 - check % 9) > 3) continue;
            hexagon->twoTileNeighbours.push_back(fields[check]);
        }
    }
}


Owner Board::playerMoves(sf::Vector2f mousePositionView, Owner player) {
    for (Node *node: blocksToCopyTo) {
        node->update(mousePositionView);
        if (node->getPressed()) {
            nodeCopy(node, player);
            if (player == Owner::Red)player = Owner::Blue;
            else if (player == Owner::Blue)player = Owner::Red;
        }
    }
    for (Node *node: blocksToJumpTo) {
        node->update(mousePositionView);
        if (node->getPressed()) {
            nodeJump(node, player);
            if (player == Owner::Red)player = Owner::Blue;
            else if (player == Owner::Blue)player = Owner::Red;
        }
    }
    return player;
}

void Board::noMovesCheck() {
    bool redcanmove = false;
    bool bluecanmove = false;
    for (Node *hexagon: fields) {
        if (redcanmove && bluecanmove) break;
        if (hexagon->getTeam() == Owner::None || hexagon->getTeam() == Owner::Nothing) continue;
        for (Node *hex: hexagon->oneTileNeighbours) {
            if (hex->getTeam() == Owner::None) {
                if (hexagon->getTeam() == Owner::Red) redcanmove = true;
                if (hexagon->getTeam() == Owner::Blue) bluecanmove = true;
            }
        }
        for (Node *hex: hexagon->twoTileNeighbours) {
            if (hex->getTeam() == Owner::None) {
                if (hexagon->getTeam() == Owner::Red) redcanmove = true;
                if (hexagon->getTeam() == Owner::Blue) bluecanmove = true;
            }
        }
    }
    if (!redcanmove)
        for (Node *hexagon: fields)
            if (hexagon->getTeam() == Owner::None)
                hexagon->setTeam(Owner::Blue);
    if (!bluecanmove)
        for (Node *hexagon: fields)
            if (hexagon->getTeam() == Owner::None)
                hexagon->setTeam(Owner::Red);
}

void Board::setlastClicked(Node *last) {
    this->lastClicked = last;
}

void Board::checkNeighbours(Node *node) {
    blocksToCopyTo.clear();
    blocksToJumpTo.clear();
    for (Node *hexagon: node->oneTileNeighbours) {
        if (hexagon->getTeam() == Owner::None) blocksToCopyTo.push_back(hexagon);
    }
    for (Node *hexagon: node->twoTileNeighbours) {
        if (hexagon->getTeam() == Owner::None) blocksToJumpTo.push_back(hexagon);
    }
}

void Board::convertNeighbours(Node *node, Owner player) {
    for (Node *hexagon: node->oneTileNeighbours) {
        if (hexagon->getTeam() == Owner::None || hexagon->getTeam() == Owner::Nothing ||
            hexagon->getTeam() == player)
            continue;
        if (hexagon->getTeam() != player) hexagon->setTeam(player);
    }
}

void Board::nodeCopy(Node *node, Owner player) {
    node->setTeam(player);
    convertNeighbours(node, player);
    blocksToCopyTo.clear();
    blocksToJumpTo.clear();
}

void Board::nodeJump(Node *node, Owner player) {
    lastClicked->setTeam(Owner::None);
    node->setTeam(player);
    convertNeighbours(node, player);
    blocksToCopyTo.clear();
    blocksToJumpTo.clear();
}
