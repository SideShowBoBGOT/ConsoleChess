#include "King.h"
std::vector<std::pair<int, int>> King::getGeneralMoves(const std::vector<Figure*>& figuresOwn,
    const std::vector<Figure*>& figuresEnemy) {
    std::vector<std::pair<int, int>> moves;
    filter(figuresOwn, figuresEnemy, moves, x, y - 1);
    filter(figuresOwn, figuresEnemy, moves, x + 1, y - 1);
    filter(figuresOwn, figuresEnemy, moves, x + 1, y);
    filter(figuresOwn, figuresEnemy, moves, x + 1, y + 1);
    filter(figuresOwn, figuresEnemy, moves, x, y + 1);
    filter(figuresOwn, figuresEnemy, moves, x - 1, y + 1);
    filter(figuresOwn, figuresEnemy, moves, x - 1, y);
    filter(figuresOwn, figuresEnemy, moves, x - 1, y - 1);
    return moves;
}
King::King(int x, int y) :Figure(x, y) {};
char King::getSymb() {
    return symb;
}