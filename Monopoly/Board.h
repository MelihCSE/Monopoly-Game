#pragma once
#include "Tile.h"
#include <vector>


class Board{
public:
    Board();
    ~Board() {} 
    Tile& getTile(int position)const;
    
private:
    std::vector<std::unique_ptr<Tile>> tiles;
};