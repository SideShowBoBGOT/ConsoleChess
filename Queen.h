#pragma once
#include "Figure.h"
class Queen : public Figure {
private:
    std::vector<std::pair<int, int>> getGeneralMoves(const std::vector<Figure*>& figuresOwn,
        const std::vector<Figure*>& figuresEnemy);
    char symb = 'Q';
public:
    Queen(int x, int y);
    char getSymb() override;
};

