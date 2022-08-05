#include "Player.h"
Player::Player() {}
Player::Player(int number) {
    if (number == 1) {
        for (int i = 0; i < 8; i++)
            figures.push_back(new Pawn(i, 1, 'd'));
        figures.push_back(new Rook(0, 0));
        figures.push_back(new Rook(7, 0));
        figures.push_back(new Knight(1, 0));
        figures.push_back(new Knight(6, 0));
        figures.push_back(new Bishop(2, 0));
        figures.push_back(new Bishop(5, 0));
        figures.push_back(new Queen(4, 0));
        figures.push_back(new King(3, 0));
    }
    else if (number == 2) {
        for (int i = 0; i < 8; i++)
            figures.push_back(new Pawn(i, 6, 'u'));
        figures.push_back(new Rook(0, 7));
        figures.push_back(new Rook(7, 7));
        figures.push_back(new Knight(1, 7));
        figures.push_back(new Knight(6, 7));
        figures.push_back(new Bishop(2, 7));
        figures.push_back(new Bishop(5, 7));
        figures.push_back(new Queen(4, 7));
        figures.push_back(new King(3, 7));
    }
}
std::vector<std::pair<int, int>> Player::getPosMoves(Figure* figure, Player& enemy) {
    Figure* king = nullptr;
    for (const auto fig : figures)
    {
        if (!strcmp(typeid(*fig).name(), typeid(King).name())) {
            king = fig;
        }
    }
    std::vector<std::pair<int, int>> posMoves = figure->getMoves(figures, enemy.figures, king);
    return posMoves;
}