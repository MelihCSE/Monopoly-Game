#pragma once
#include <string>

class Player;
class Game; 

class ChanceCard {
public:
    ChanceCard(const std::string& text) : text(text) {}
    virtual ~ChanceCard() = default; 
    virtual void apply(Player& player, Game& game) = 0;
    std::string getText() const { return text; }

protected: 
    std::string text;
};

class MoneyCard : public ChanceCard {
public:
    MoneyCard(const std::string& text, int amount);
    void apply(Player& player, Game& game) override;
    int getAmount() const { return amount; }

private:
    int amount;
};

class MoveCard : public ChanceCard {
public:
    MoveCard(const std::string& text, int targetPosition);
    void apply(Player& player, Game& game) override;
    int getTargetPosition() const { return targetPosition; }

private:
    int targetPosition; 
};