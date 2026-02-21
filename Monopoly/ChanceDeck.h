#pragma once
#include "ChanceCard.h"
#include <vector>
#include <memory>

class ChanceDeck {
public:
    ChanceDeck();
    void shuffle();
    ChanceCard* drawCard();
    
private:
    std::vector<std::unique_ptr<ChanceCard>> cardList;
    size_t currentCardIndex;
};