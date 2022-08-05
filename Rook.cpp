#include "Rook.h"
std::vector<std::pair<int, int>> Rook::getGeneralMoves(const std::vector<Figure*>& figuresOwn,
    const std::vector<Figure*>& figuresEnemy) {
    std::vector<std::pair<int, int>> moves;
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
char Rook::getSymb()  {
    return symb;
}
Rook::Rook(int x, int y) :Figure(x, y) {};
std::vector<std::pair<int, int>> Rook::getMoves(std::vector<Figure*>& figuresOwn,
    std::vector<Figure*>& figuresEnemy, Figure* king) {
    std::vector<std::pair<int, int>> moves = Figure::getMoves(figuresOwn, figuresEnemy, king);
    //castling
    if (!isMoved && !king->getIsMoved()) {
        //is path free
        bool isFree = true;
        if (x == 0) {
            for (const auto fig : figuresOwn) {
                if (x + 1 == fig->x && y == fig->y ||
                    x + 2 == fig->x && y == fig->y) {
                    isFree = false;
                    break;
                }
            }
        }
        else if (x == 7) {
            for (const auto fig : figuresOwn) {
                if (x - 1 == fig->x && y == fig->y ||
                    x - 2 == fig->x && y == fig->y ||
                    x - 3 == fig->x && y == fig->y) {
                    isFree = false;
                    break;
                }
            }
        }
        if (isFree) {
            Figure* enemyKing = nullptr;
            for (const auto fig : figuresEnemy)
            {
                if (king->getSymb() == fig->getSymb()) {
                    enemyKing = fig;
                    break;
                }
            }
            //if path is under attack
            bool isPathAttacked = false;
            if (x == 0) {
                for (const auto fig : figuresEnemy)
                {
                    for (const auto& m : fig->getMoves(figuresEnemy, figuresOwn, enemyKing))
                    {
                        if (x + 1 == m.first && y == m.second ||
                            x + 2 == m.first && y == m.second) {
                            bool isPathAttacked = true;
                            break;
                        }

                    }
                }
            }
            else if (x == 7) {
                for (const auto fig : figuresEnemy)
                {
                    for (const auto& m : fig->getMoves(figuresEnemy, figuresOwn, enemyKing))
                    {
                        if (x - 1 == m.first && y == m.second ||
                            x - 2 == m.first && y == m.second ||
                            x - 3 == m.first && y == m.second) {
                            bool isPathAttacked = true;
                            break;
                        }

                    }
                }
            }
            if (!isPathAttacked) {
                //if king is in check
                auto check = [&enemyKing, &figuresEnemy, &figuresOwn, &king]() {
                    for (const auto fig : figuresEnemy)
                    {
                        for (const auto& m : fig->getMoves(figuresEnemy, figuresOwn, enemyKing))
                        {
                            if (m.first == king->x && m.second == king->y) {
                                return true;
                            }
                        }
                    }
                    return false;
                };
                if (!check()) {
                    //check if king is in check after castling
                    std::pair<int, int> initPosKing = std::pair<int, int>(king->x, king->y);
                    std::pair<int, int> initPosRook = std::pair<int, int>(x, y);
                    if (x == 0) {
                        this->x = 2;
                        king->x = 1;
                        if (!check())
                            moves.push_back(initPosKing);
                        this->x = initPosRook.first;
                        king->x = initPosKing.first;
                    }
                    else if (x == 7) {
                        this->x = 4;
                        king->x = 5;
                        if (!check())
                            moves.push_back(initPosKing);
                        this->x = initPosRook.first;
                        king->x = initPosKing.first;
                    }
                }
            }
        }
    }
    return moves;
}