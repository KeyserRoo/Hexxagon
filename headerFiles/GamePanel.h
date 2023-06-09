#ifndef HEXXAGON_GAMEPANEL_H
#define HEXXAGON_GAMEPANEL_H

#include "Panel.h"
#include "Node.h"
#include "PauseMenu.h"
#include <vector>
#include "Board.h"
#include "Background.h"

class GamePanel : public Panel {
public:
    explicit GamePanel(sf::RenderWindow *window, std::stack<Panel *> *states);

    ~GamePanel();


    void update(const float &deltaTime) override;

    void updateInput(const float &deltaTime) override;


    void render(sf::RenderTarget *target) override;

private:

    bool pause;
    Button *pauseButton;
    PauseMenu *pauseMenu;
    sf::Texture *pauseTexture;

    int neutralLeft;
    int playerRedScore;
    int playerBlueScore;

    bool gameRuns;

    Owner player;

    sf::Font *font;
    sf::Text redText;
    sf::Text blueText;
    sf::RectangleShape redBar;
    sf::RectangleShape blueBar;

    Button *winQuit;
    sf::Text *winText;
    sf::RectangleShape *winBar;
    sf::RectangleShape *winScreen;


    void updateScore();

    void updateButtons();

    void updatePauseButtons();


    void renderScore(sf::RenderTarget *target);

    void renderWinScreen(sf::RenderTarget *target);


    void initializeScore();

    void initializeButtons();

    void initializeWinScreen();


    void calculateScore();


    void pauseGame();

    void unpauseGame();
};

#endif //HEXXAGON_GAMEPANEL_H