#pragma once
#include <string>

class Player {
private:
    std::string name;
    int money;
    int position;

public:
    Player(const std::string& name);
    int getPosition() const;
    int getMoney() const;
    std::string getName() const;
    void move(int steps);
    void changeMoney(int amount);
    void changePosition(int newPosition);
};