#include "Bishop.h"
std::vector<std::pair<int, int>> Bishop::getGeneralMoves(const std::vector<Figure*>& figuresOwn,
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
    return moves;
}
Bishop::Bishop(int x, int y) :Figure(x, y) {};
char Bishop::getSymb() {
    return symb;
}