#pragma once
#include <vector>
#include "Figure.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
class Player {
public:
    std::vector<Figure*> figures;
    std::vector<Figure*> takenFigures;
    Player();
    Player(int number);
    std::vector<std::pair<int, int>> getPosMoves(Figure* figure, Player& enemy);
};
