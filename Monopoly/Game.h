#pragma once
#include "Player.h"
#include "Board.h"
#include "Dice.h"
#include "ChanceDeck.h"
#include <vector>

class Game {
public:
    Game();
    void start();
    void playTurn();
    void addPlayer(const std::string& name);
    void showScores() const;
    void checkBankruptcy();
    ChanceDeck& getChanceDeck();
    const std::vector<Player>& getPlayers() const;
    Player& getCurrentPlayer();

private:
    std::vector<Player> players;
    Board board;
    Dice dice;
    ChanceDeck chancedeck;
    int currentPlayerIndex;
    bool gameOver;
};