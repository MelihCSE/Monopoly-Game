#include "Player.h"
#include <iostream>

Player::Player(const std::string& name): name(name), money(1500), position(0) {}

int Player::getMoney() const { 
    return money; 
}

int Player::getPosition() const { 
    return position; 
}

void Player::move(int steps) {
    int oldPosition = position;
    position = (position + steps) % 40; // Tahta 40 kareli
    
    // Eğer Start'tan geçtiyse (pozisyon küçüldüyse) 200$ al
    if (position < oldPosition) {
        money += 200;
        std::cout << name << " Start'tan gecti ve 200$ aldi!" << std::endl;
    }
}

void Player::changeMoney(int amount) {
    money += amount;
    std::cout << name << " parasini degistirdi: " << amount << "$ (Toplam: " << money << "$)" << std::endl;
}

void Player::changePosition(int newPosition) {
    position = newPosition % 40;
    if (position < 0) position += 40;
}

std::string Player::getName() const {
    return name;
}