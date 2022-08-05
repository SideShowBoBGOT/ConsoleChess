#include "Queen.h"
Queen::Queen(int x, int y) :Figure(x, y) {};
char Queen::getSymb() {
    return symb;
}
std::vector<std::pair<int, int>> Queen::getGeneralMoves(const std::vector<Figure*>& figuresOwn,
    const std::vector<Figure*>& figuresEnemy) {
    std::vector<std::pair<int, int>> moves;
    for (int i = 1, j = 1; i <= y && j < 8 - x; i++, j++)
        if (!filter(figuresOwn, figuresEnemy, moves, x + j, y - i))
            break;
    for (int i = 1, j = 1; i < 8 - y && j < 8 - x; i++, j++)
        if (!filter(figuresOwn, figuresEnemy, moves, x + j, y + i))
            break;
    for (int i = 1, j = 1; i < 8 - y && j <= x; i++, j++)
        if (!filter(figuresOwn, figuresEnemy, moves, x - j, y + i))
            break;
    for (int i = 1, j = 1; i <= y && j <= x; i++, j++)
        if (!filter(figuresOwn, figuresEnemy, moves, x - j, y - i))
            break;
    for (int i = 1; i < 8 - y; i++)
        if (!filter(figuresOwn, figuresEnemy, moves, x, y + i))
            break;
    for (int i = 1; i <= y; i++)
        if (!filter(figuresOwn, figuresEnemy, moves, x, y - i))
            break;
    for (int i = 1; i < 8 - x; i++)
        if (!filter(figuresOwn, figuresEnemy, moves, x + i, y))
            break;
    for (int i = 1; i <= x; i++)
        if (!filter(figuresOwn, figuresEnemy, moves, x - i, y))
            break;
    return moves;
}