#pragma once
#include <string>

class Player;
class Game;

class Tile {
public:
    virtual ~Tile() = default;
    virtual void apply(Player& p, Game& game) = 0;
};