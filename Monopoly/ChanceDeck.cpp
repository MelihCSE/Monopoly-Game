#include "ChanceDeck.h"
#include <iostream>
#include <algorithm>
#include <random>

ChanceDeck::ChanceDeck() : currentCardIndex(0) {
    cardList.push_back(std::make_unique<MoneyCard>("Banka hatasi - Lehine 200$ al", 200));
    cardList.push_back(std::make_unique<MoneyCard>("Doktor masraflari - 50$ ode", -50));
    cardList.push_back(std::make_unique<MoneyCard>("Yil donumu primi - 100$ al", 100));
    cardList.push_back(std::make_unique<MoneyCard>("Vergi iadesi - 150$ al", 150));
    cardList.push_back(std::make_unique<MoneyCard>("Hastane masraflari - 100$ ode", -100));
    cardList.push_back(std::make_unique<MoneyCard>("Yatirimdan kar - 50$ al", 50));
    cardList.push_back(std::make_unique<MoneyCard>("Okul masraflari - 150$ ode", -150));
    cardList.push_back(std::make_unique<MoveCard>("Baslangiç noktasina git", 0));
    cardList.push_back(std::make_unique<MoveCard>("Boardwalk'a ilerle", 39));
    cardList.push_back(std::make_unique<MoveCard>("Illinois Avenue'ya git", 24));
    cardList.push_back(std::make_unique<MoneyCard>("Yarismadan ikinci oldun - 10$ al", 10));
    cardList.push_back(std::make_unique<MoneyCard>("Tahsilat - 50$ al", 50));
    
    shuffle();
}

void ChanceDeck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cardList.begin(), cardList.end(), g);
    currentCardIndex = 0;
}

ChanceCard* ChanceDeck::drawCard() {
    if (cardList.empty()) return nullptr;
    
    ChanceCard* card = cardList[currentCardIndex].get();
    currentCardIndex = (currentCardIndex + 1) % cardList.size();
    
    // Destede dön
    if (currentCardIndex == 0) {
        shuffle();
    }
    
    return card;
}