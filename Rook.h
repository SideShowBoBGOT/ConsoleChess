#pragma once
#include "Figure.h"
class Rook : public Figure
{
private:
    std::vector<std::pair<int, int>> getGeneralMoves(const std::vector<Figure*>& figuresOwn,
        const std::vector<Figure*>& figuresEnemy);
    char symb = 'I';
public:
    char getSymb() override;
    Rook(int x, int y);
    virtual std::vector<std::pair<int, int>> getMoves(std::vector<Figure*>& figuresOwn,
        std::vector<Figure*>& figuresEnemy, Figure* king);
};

