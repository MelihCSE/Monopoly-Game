#include "Board.h"
#include "Game.h"
#include "ChanceDeck.h"
#include "ChanceCard.h"
#include <memory>

class PropertyTile : public Tile {
private:
    std::string name;
    int price;
    int rent;
    Player* owner;
    
public:
    PropertyTile(const std::string& name, int price, int rent) 
        : name(name), price(price), rent(rent), owner(nullptr) {}
    
    void apply(Player& p, Game& game) override {
        
        if (owner != nullptr && owner != &p) {
            p.changeMoney(-rent);
            owner->changeMoney(rent);
        }
    }
};

class ChanceTile : public Tile {
public:
    void apply(Player& p, Game& game) override {
        // Şans kartı çek
        ChanceCard* card = game.getChanceDeck().drawCard();
        if (card) {
            card->apply(p, game);
        }
    }
};

class GoTile : public Tile {
public:
    void apply(Player& p, Game& game) override {
        // Başlangıç noktası - para al
        p.changeMoney(200);
    }
};

class TaxTile : public Tile {
private:
    int taxAmount;
    
public:
    TaxTile(int amount) : taxAmount(amount) {}
    
    void apply(Player& p, Game& game) override {
        // Vergi öde
        p.changeMoney(-taxAmount);
    }
};

class FreeParkingTile : public Tile {
public:
    void apply(Player& p, Game& game) override {
        // Ücretsiz park - hiçbir şey olmuyor
    }
};

class JailTile : public Tile {
public:
    void apply(Player& p, Game& game) override {
        // Hapishane ziyareti (sadece ziyaret)
    }
};

Board::Board() {
    // 40 kareli standart Monopoly tahtası oluştur
    tiles.push_back(std::make_unique<GoTile>());                          // 0: Start
    tiles.push_back(std::make_unique<PropertyTile>("Mediterranean Ave", 60, 2));   // 1
    tiles.push_back(std::make_unique<ChanceTile>());                      // 2
    tiles.push_back(std::make_unique<PropertyTile>("Baltic Ave", 60, 4));         // 3
    tiles.push_back(std::make_unique<TaxTile>(200));                      // 4: Income Tax
    tiles.push_back(std::make_unique<PropertyTile>("Reading Railroad", 200, 25)); // 5
    tiles.push_back(std::make_unique<PropertyTile>("Oriental Ave", 100, 6));      // 6
    tiles.push_back(std::make_unique<ChanceTile>());                      // 7
    tiles.push_back(std::make_unique<PropertyTile>("Vermont Ave", 100, 6));       // 8
    tiles.push_back(std::make_unique<PropertyTile>("Connecticut Ave", 120, 8));   // 9
    tiles.push_back(std::make_unique<JailTile>());                        // 10: Jail
    tiles.push_back(std::make_unique<PropertyTile>("St. Charles Place", 140, 10)); // 11
    tiles.push_back(std::make_unique<PropertyTile>("Electric Company", 150, 0));   // 12
    tiles.push_back(std::make_unique<PropertyTile>("States Ave", 140, 10));       // 13
    tiles.push_back(std::make_unique<PropertyTile>("Virginia Ave", 160, 12));     // 14
    tiles.push_back(std::make_unique<PropertyTile>("Pennsylvania Railroad", 200, 25)); // 15
    tiles.push_back(std::make_unique<PropertyTile>("St. James Place", 180, 14));  // 16
    tiles.push_back(std::make_unique<ChanceTile>());                      // 17
    tiles.push_back(std::make_unique<PropertyTile>("Tennessee Ave", 180, 14));    // 18
    tiles.push_back(std::make_unique<PropertyTile>("New York Ave", 200, 16));     // 19
    tiles.push_back(std::make_unique<FreeParkingTile>());                 // 20: Free Parking
    tiles.push_back(std::make_unique<PropertyTile>("Kentucky Ave", 220, 18));     // 21
    tiles.push_back(std::make_unique<ChanceTile>());                      // 22
    tiles.push_back(std::make_unique<PropertyTile>("Indiana Ave", 220, 18));      // 23
    tiles.push_back(std::make_unique<PropertyTile>("Illinois Ave", 240, 20));     // 24
    tiles.push_back(std::make_unique<PropertyTile>("B&O Railroad", 200, 25));     // 25
    tiles.push_back(std::make_unique<PropertyTile>("Atlantic Ave", 260, 22));     // 26
    tiles.push_back(std::make_unique<PropertyTile>("Ventnor Ave", 260, 22));      // 27
    tiles.push_back(std::make_unique<PropertyTile>("Water Works", 150, 0));       // 28
    tiles.push_back(std::make_unique<PropertyTile>("Marvin Gardens", 280, 24));   // 29
    tiles.push_back(std::make_unique<JailTile>());                        // 30: Go to Jail
    tiles.push_back(std::make_unique<PropertyTile>("Pacific Ave", 300, 26));      // 31
    tiles.push_back(std::make_unique<PropertyTile>("North Carolina Ave", 300, 26)); // 32
    tiles.push_back(std::make_unique<ChanceTile>());                      // 33
    tiles.push_back(std::make_unique<PropertyTile>("Pennsylvania Ave", 320, 28)); // 34
    tiles.push_back(std::make_unique<PropertyTile>("Short Line Railroad", 200, 25)); // 35
    tiles.push_back(std::make_unique<ChanceTile>());                      // 36
    tiles.push_back(std::make_unique<PropertyTile>("Park Place", 350, 35));       // 37
    tiles.push_back(std::make_unique<TaxTile>(100));                      // 38: Luxury Tax
    tiles.push_back(std::make_unique<PropertyTile>("Boardwalk", 400, 50));        // 39
}

Tile& Board::getTile(int position) const {
    // Position'ı 40'a modulo al (tahta 40 kare)
    position = position % 40;
    if (position < 0) position += 40;
    return *tiles[position];
}