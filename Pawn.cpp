#include "Pawn.h"
Pawn::Pawn(int x, int y, char direction) :Figure(x, y) {
    this->direction = direction;
};
char Pawn::getDirection() {
    return direction;
}
char Pawn::getSymb()  {
    return symb;
}
bool Pawn::filter(const std::vector<Figure*>& figuresOwn, const std::vector<Figure*>& figuresEnemy,
    std::vector<std::pair<int, int>>& moves, int x, int y)  {
    for (const auto fig : figuresOwn)
        if (x == fig->x && y == fig->y)
            return false;
    for (const auto fig : figuresEnemy)
    {
        if (x == fig->x && y == fig->y) {
            return false;
        }
    }
    moves.push_back(std::pair<int, int>(x, y));
    return true;
}
std::vector<std::pair<int, int>> Pawn::getGeneralMoves(const std::vector<Figure*>& figuresOwn,
    const std::vector<Figure*>& figuresEnemy) {
    std::vector<std::pair<int, int>> moves;
    if (direction == 'd') {
        if (filter(figuresOwn, figuresEnemy, moves, x, y + 1)) {
            if (!isMoved)
                filter(figuresOwn, figuresEnemy, moves, x, y + 2);
        }
        for (const auto figure : figuresEnemy)
        {
            if (figure->x == x - 1 && figure->y == y + 1)
                moves.push_back(std::pair<int, int>(x - 1, y + 1));
            if (figure->x == x + 1 && figure->y == y + 1)
                moves.push_back(std::pair<int, int>(x + 1, y + 1));
        }

    }
    else if (direction == 'u') {
        if (filter(figuresOwn, figuresEnemy, moves, x, y - 1)) {
            if (!isMoved)
                filter(figuresOwn, figuresEnemy, moves, x, y - 2);
        }
        for (const auto figure : figuresEnemy)
        {
            if (figure->x == x - 1 && figure->y == y - 1)
                moves.push_back(std::pair<int, int>(x - 1, y - 1));
            if (figure->x == x + 1 && figure->y == y - 1)
                moves.push_back(std::pair<int, int>(x + 1, y - 1));
        }
    }
    return moves;
}