#pragma once
#include "Figure.h"
class Pawn : public Figure {
private:
    char direction;
    bool filter(const std::vector<Figure*>& figuresOwn, const std::vector<Figure*>& figuresEnemy,
        std::vector<std::pair<int, int>>& moves, int x, int y) override;
    std::vector<std::pair<int, int>> getGeneralMoves(const std::vector<Figure*>& figuresOwn,
        const std::vector<Figure*>& figuresEnemy);
    char symb = '6';
public:
    Pawn(int x, int y, char direction);
    char getDirection();
    char getSymb() override;
};

