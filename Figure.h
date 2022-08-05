#pragma once
#include <iostream>
#include <vector>
class Figure {
protected:
    bool isMoved = false;
    virtual bool filter(const std::vector<Figure*>& figuresOwn, const std::vector<Figure*>& figuresEnemy,
        std::vector<std::pair<int, int>>& moves, int x, int y);
    virtual std::vector<std::pair<int, int>> getGeneralMoves(const std::vector<Figure*>& figuresOwn,
        const std::vector<Figure*>& figuresEnemy) = 0;
public:
    int x;
    int y;
    Figure(int x, int y);
    void setMoved();
    bool getIsMoved();
    virtual char getSymb() = 0;
    virtual std::vector<std::pair<int, int>> getMoves(std::vector<Figure*>& figuresOwn,
        std::vector<Figure*>& figuresEnemy, Figure* king);
};

