#include "ChanceCard.h"
#include "Player.h"
#include "Game.h"
#include <iostream>

MoneyCard::MoneyCard(const std::string& text, int amount)
    : ChanceCard(text), amount(amount) {}

void MoneyCard::apply(Player& player, Game& game) {
    player.changeMoney(amount);
    std::cout << "Sans Karti: " << text << std::endl;
    if (amount > 0) {
        std::cout << player.getName() << " " << amount << "$ kazandi!" << std::endl;
    } else {
        std::cout << player.getName() << " " << (-amount) << "$ kaybetti!" << std::endl;
    }
}

MoveCard::MoveCard(const std::string& text, int targetPosition)
    : ChanceCard(text), targetPosition(targetPosition) {}

void MoveCard::apply(Player& player, Game& game) {
    std::cout << "Sans Karti: " << text << std::endl;
    int oldPos = player.getPosition();
    player.changePosition(targetPosition);
    
    // Eğer ileri gittiyse ve Start'tan geçtiyse para al
    if (targetPosition < oldPos) {
        player.changeMoney(200);
        std::cout << player.getName() << " Start'tan gecti ve 200$ aldi!" << std::endl;
    }
    
    std::cout << player.getName() << " " << targetPosition << " numarali kareye gitti!" << std::endl;
}

// Getters implemented in header inline, nothing else to add here.