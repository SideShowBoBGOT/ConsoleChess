#pragma once
#include <string.h>
#include "Figure.h"
class King : public Figure {
private:
    std::vector<std::pair<int, int>> getGeneralMoves(const std::vector<Figure*>& figuresOwn,
        const std::vector<Figure*>& figuresEnemy);
    char symb = 'K';
public:
    King(int x, int y);
    char getSymb() override;
};

