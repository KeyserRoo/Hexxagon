#include <iostream>
#include <sstream>
#include "string"
#include "cmath"
#include "../headerFiles/GamePanel.h"

GamePanel::GamePanel(sf::RenderWindow *window, std::stack<Panel *> *states) : Panel(window, states) {
    pauseMenu = new PauseMenu(*window);
    pause = false;

    board = new Board();

    neutralLeft = 58;
    player = Owner::Red;
    gameRuns = true;

    initializeButtons();
    initializeScore();
    initializeWinScreen();
}

GamePanel::~GamePanel() {
    delete pauseMenu;
    delete pauseTexture;
    delete pauseButton;

    delete winBar;
    delete winText;
    delete winScreen;
    delete winQuit;

    delete font;
    delete board;
}


void GamePanel::update(const float &deltaTime) {
    updateMousePositions();
    if (gameRuns) {
        if (pause) {
            pauseMenu->update(mousePositionView);
            updatePauseButtons();
        } else {
            pauseButton->update(mousePositionView);
            for (Node *hexagon: board->getFields()) {
                hexagon->updateTeam();
            }
            updateButtons();
        }
        if (neutralLeft == 0) {
            if (playerRedScore > playerBlueScore)winBar->setFillColor(Node::setColorRed());
            else if (playerRedScore < playerBlueScore)winBar->setFillColor(Node::setColorBlue());
            else {
                winBar->setFillColor(Node::setColorNone());
                winText->setString("Draw Royale!");
                winText->setPosition(winBar->getPosition() - sf::Vector2f(360, 80));
            }
            gameRuns = false;
        }
    } else {
        winQuit->update(mousePositionView);
        updateButtons();
    }
}

void GamePanel::updateInput(const float &deltaTime) {
    if (!gameRuns) return;
    if (pause) return;
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;
    for (Node *hexagon: board->getFields()) {
        if (hexagon->getTeam() == Owner::Red || hexagon->getTeam() == Owner::Blue)
            hexagon->update(mousePositionView);
        if (hexagon->getPressed() && hexagon->getTeam() == player) {
            board->setlastClicked(hexagon);
            board->checkNeighbours(hexagon);
        }
    }
    player = board->playerMoves(mousePositionView,player);
    board->noMovesCheck();
    updateScore();
}

void GamePanel::updateScore() {
    calculateScore();

    std::stringstream ssr;
    ssr << playerRedScore;
    std::string strr = ssr.str();
    redText.setString(strr);

    std::stringstream ssb;
    ssb << playerBlueScore;
    std::string strb = ssb.str();
    blueText.setString(strb);

    redBar.setSize({10.f * playerRedScore, 40});
    blueBar.setSize({10.f * playerBlueScore, 40});
}

void GamePanel::updateButtons() {
    if (this->pauseButton->isPressed) pauseGame();
    if (this->winQuit->isPressed) ends = true;
}

void GamePanel::updatePauseButtons() {
    if (this->pauseMenu->resume->isPressed) unpauseGame();
    if (this->pauseMenu->quit->isPressed) ends = true;
}


void GamePanel::render(sf::RenderTarget *target) {
    for (Node *hexagon: board->getFields()) {
        hexagon->renderHex(target);
    }
    renderScore(target);
    board->renderNeighbours(target);
    pauseButton->renderImageButton(target);
    if (!gameRuns)renderWinScreen(target);
    if (pause) this->pauseMenu->render(*target);
}

void GamePanel::renderScore(sf::RenderTarget *target) {
    target->draw(redBar);
    target->draw(blueBar);
    target->draw(redText);
    target->draw(blueText);
}

void GamePanel::calculateScore() {
    playerRedScore = 0;
    playerBlueScore = 0;
    neutralLeft = 58;
    for (Node *hexagon: board->getFields()) {
        if (hexagon->getTeam() == Owner::Red) playerRedScore++;
        if (hexagon->getTeam() == Owner::Blue) playerBlueScore++;
    }
    neutralLeft -= playerRedScore + playerBlueScore;
}

void GamePanel::renderWinScreen(sf::RenderTarget *target) {
    target->draw(*winScreen);
    target->draw(*winBar);
    target->draw(*winText);
    winQuit->renderTextButton(target);
}






void GamePanel::initializeScore() {
    font = new sf::Font;
    std::string fontLocation = "..\\resourceFiles\\arial.ttf";
    if (!font->loadFromFile(fontLocation)) {
        std::cout << "Could not load font from:   " << fontLocation;
    }
    redText.setFont(*font);
    redText.setCharacterSize(35);
    redText.setOutlineThickness(2.5f);
    redText.setFillColor(Node::setColorRed());
    redText.setPosition(350, 900);

    redBar.setFillColor(Node::setColorRed());
    redBar.setPosition(347, 902);

    blueText.setFont(*font);
    blueText.setCharacterSize(35);
    blueText.setOutlineThickness(2.5f);
    blueText.setFillColor(Node::setColorBlue());
    blueText.setPosition(350, 850);

    blueBar.setFillColor(Node::setColorBlue());
    blueBar.setPosition(347, 852);
}

void GamePanel::initializeButtons() {
    pauseTexture = new sf::Texture();
    std::string filename = "..\\resourceFiles\\settings.png";
    if (!pauseTexture->loadFromFile(filename)) {
        std::cout << "could not load font from:   " << filename;
    }
    pauseButton = new Button(sf::Vector2f(1, 1), sf::Vector2f(100, 100), pauseTexture);
}

void GamePanel::initializeWinScreen() {
    winScreen = new sf::RectangleShape;
    winScreen->setSize({1920, 1080});
    winScreen->setFillColor(sf::Color(100, 100, 100, 150));


    winBar = new sf::RectangleShape;
    winBar->setSize({1000, 200});
    winBar->setOrigin(500, 100);
    winBar->setPosition(960, 540);


    winText = new sf::Text;
    winText->setCharacterSize(120);
    winText->setString("Victory Royale!");
    winText->setPosition(winBar->getPosition() - sf::Vector2f(400, 80));
    winText->setFont(*font);
    winText->setOutlineThickness(5);

    winQuit = new Button("Quit", font, sf::Vector2f(150, 80),
                         sf::Vector2f(885, 900),
                         sf::Color::Black,
                         sf::Color::Black,
                         sf::Color::Black);
}

void GamePanel::pauseGame() {
    this->pause = true;
}

void GamePanel::unpauseGame() {
    this->pause = false;
}