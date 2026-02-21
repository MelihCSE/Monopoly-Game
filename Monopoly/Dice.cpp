#include "Dice.h"

Dice::Dice() {
    srand(static_cast<unsigned>(std::time(nullptr)));
}
int Dice::roll(){
    return (rand() % 6) + 1;
}