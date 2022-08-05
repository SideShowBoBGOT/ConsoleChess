#pragma once
#include "Figure.h"
class Knight : public Figure
{
private:
    std::vector<std::pair<int, int>> getGeneralMoves(const std::vector<Figure*>& figuresOwn,
        const std::vector<Figure*>& figuresEnemy);
    char symb = '$';
public:
    Knight(int x, int y);
    char getSymb() override;
};
