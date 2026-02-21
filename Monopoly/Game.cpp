#include "Game.h"
#include <iostream>
#include <limits>

Game::Game() : currentPlayerIndex(0), gameOver(false) {}

void Game::addPlayer(const std::string& name) {
    players.push_back(Player(name));
    std::cout << name << " oyuna katildi! (Baslangic parasi: 1500$)" << std::endl;
}

void Game::playTurn() {
    if (players.empty() || gameOver) return;
    
    Player& p = players[currentPlayerIndex];
    
    std::cout << "\n========================================" << std::endl;
    std::cout << p.getName() << "'in sirasi!" << std::endl;
    std::cout << "Pozisyon: " << p.getPosition() << " | Para: " << p.getMoney() << "$" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Zar at
    int roll = dice.roll();
    std::cout << "Zar: " << roll << std::endl;
    
    // Hareket et
    p.move(roll);
    std::cout << p.getName() << " " << p.getPosition() << " numarali kareye geldi." << std::endl;
    
    // Kare etkisini uygula
    Tile& tile = board.getTile(p.getPosition());
    tile.apply(p, *this);
    
    // Sonraki oyuncuya geç
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void Game::start() {
    std::cout << "\n====== MONOPOLY OYUNU BASLIYOR ======\n" << std::endl;
    
    // Oyuncu ekle
    std::string playerName;
    int numPlayers;
    
    std::cout << "Kac oyuncu oynayacak? (2-4): ";
    std::cin >> numPlayers;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (numPlayers < 2) numPlayers = 2;
    if (numPlayers > 4) numPlayers = 4;
    
    for (int i = 0; i < numPlayers; i++) {
        std::cout << "Oyuncu " << (i + 1) << " ismi: ";
        std::getline(std::cin, playerName);
        addPlayer(playerName);
    }
    
    std::cout << "\nOyun basliyor! Komutlar:" << std::endl;
    std::cout << "  'r' - Zar at ve tur oyna" << std::endl;
    std::cout << "  's' - Skorlari goster" << std::endl;
    std::cout << "  'q' - Cikis" << std::endl;
    
    // Oyun döngüsü
    std::string command;
    while (!gameOver) {
        std::cout << "\nKomut girin (r/s/q): ";
        std::getline(std::cin, command);
        
        if (command == "r" || command == "R") {
            playTurn();
        } else if (command == "s" || command == "S") {
            showScores();
        } else if (command == "q" || command == "Q") {
            gameOver = true;
            std::cout << "Oyun sonlandiriliyor..." << std::endl;
        } else {
            std::cout << "Gecersiz komut!" << std::endl;
        }
        
        checkBankruptcy();
    }
    
    std::cout << "\nOyun bitti! Final skorlari:" << std::endl;
    showScores();
}

void Game::showScores() const {
    std::cout << "\n===== SKORLAR =====" << std::endl;
    for (size_t i = 0; i < players.size(); i++) {
        const Player& p = players[i];
        std::cout << (i + 1) << ". " << p.getName() 
                  << " - Para: " << p.getMoney() << "$ | Pozisyon: " 
                  << p.getPosition() << std::endl;
    }
    std::cout << "===================" << std::endl;
}

void Game::checkBankruptcy() {
    int activePlayers = 0;
    for (const auto& p : players) {
        if (p.getMoney() > 0) activePlayers++;
    }
    
    if (activePlayers <= 1) {
        gameOver = true;
    }
}

ChanceDeck& Game::getChanceDeck() {
    return chancedeck;
}

const std::vector<Player>& Game::getPlayers() const {
    return players;
}

Player& Game::getCurrentPlayer() {
    return players[currentPlayerIndex];
}