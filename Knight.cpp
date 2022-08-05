#include "Knight.h"
Knight::Knight(int x, int y) :Figure(x, y) {};
char Knight::getSymb() {
    return symb;
}
std::vector<std::pair<int, int>> Knight::getGeneralMoves(const std::vector<Figure*>& figuresOwn,
    const std::vector<Figure*>& figuresEnemy) {
    std::vector<std::pair<int, int>> moves;
    filter(figuresOwn, figuresEnemy, moves, x + 1, y + 2);
    filter(figuresOwn, figuresEnemy, moves, x - 1, y + 2);
    filter(figuresOwn, figuresEnemy, moves, x + 1, y - 2);
    filter(figuresOwn, figuresEnemy, moves, x - 1, y - 2);
    filter(figuresOwn, figuresEnemy, moves, x + 2, y + 1);
    filter(figuresOwn, figuresEnemy, moves, x - 2, y + 1);
    filter(figuresOwn, figuresEnemy, moves, x + 2, y - 1);
    filter(figuresOwn, figuresEnemy, moves, x - 2, y - 1);
    return moves;
}