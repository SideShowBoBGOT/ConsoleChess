#include "Figure.h"
bool Figure::filter(const std::vector<Figure*>& figuresOwn, const std::vector<Figure*>& figuresEnemy,
    std::vector<std::pair<int, int>>& moves, int x, int y) {
    for (const auto fig : figuresOwn)
        if (x == fig->x && y == fig->y)
            return false;
    for (const auto fig : figuresEnemy)
    {
        if (x == fig->x && y == fig->y) {
            moves.push_back(std::pair<int, int>(x, y));
            return false;
        }
    }
    if (x >= 0 && y >= 0 && x < 8 && y < 8) {
        moves.push_back(std::pair<int, int>(x, y));
    }
    return true;
}
Figure::Figure(int x, int y) {
    this->x = x;
    this->y = y;
}
void Figure::setMoved() {
    isMoved = true;
}
bool Figure::getIsMoved() {
    return isMoved;
}
std::vector<std::pair<int, int>> Figure::getMoves(std::vector<Figure*>& figuresOwn,
    std::vector<Figure*>& figuresEnemy, Figure* king) {
    std::vector<std::pair<int, int>> moves = getGeneralMoves(figuresOwn, figuresEnemy);
    std::vector<std::pair<int, int>> posMoves;
    std::pair<int, int> initPos = std::pair<int, int>(x, y);
    for (const auto& pMov : moves)
    {
        this->x = pMov.first;
        this->y = pMov.second;
        bool isIn = false;
        std::vector<std::pair<int, int>> enemyMoves;
        //if there is enemy in the same square
        //we need to save him, erase from enemyFigures
        //and then restore it
        Figure* enemyFig = nullptr;
        for (auto i = begin(figuresEnemy); i != end(figuresEnemy); i++)
        {
            if ((*i)->x == x && (*i)->y == y) {
                enemyFig = std::move(*i);
                figuresEnemy.erase(i);
                break;
            }
        }

        for (const auto& fig : figuresEnemy) {
            std::vector<std::pair<int, int>> figMoves;
            figMoves = fig->getGeneralMoves(figuresEnemy, figuresOwn);
            enemyMoves.insert(enemyMoves.end(), figMoves.begin(), figMoves.end());
        }
        //restore deleted enemy figure
        if (enemyFig != nullptr)
            figuresEnemy.push_back(enemyFig);
        for (const auto& eMov : enemyMoves)
        {
            if (king->x == eMov.first && king->y == eMov.second) {
                isIn = true;
                break;
            }
        }
        if (!isIn)
            posMoves.push_back(pMov);
    }
    this->x = initPos.first;
    this->y = initPos.second;
    return posMoves;
}