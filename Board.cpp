#include "Board.h"
void Board::colorCell(int x, int y, int colorOne, int colorTwo) {
    if (x % 2 == 1) {
        if (y % 2 == 1)
            SetConsoleTextAttribute(console, colorTwo);
        else
            SetConsoleTextAttribute(console, colorOne);
    }
    else {
        if (y % 2 == 1)
            SetConsoleTextAttribute(console, colorOne);
        else
            SetConsoleTextAttribute(console, colorTwo);
    }
}
void Board::colorSelectBtn(int x, int y, int color) {
    if (selectBtnX == x && selectBtnY == y)
        SetConsoleTextAttribute(console, color);
}
void Board::colorPosMoves(int x, int y, int colorOne, int colorTwo) {
    for (const auto& pMove : posMoves)
    {
        if (pMove.first == x && pMove.second == y) {
            SetConsoleTextAttribute(console, colorOne);
            if (selectBtnX == x && selectBtnY == y)
                SetConsoleTextAttribute(console, colorTwo);
        }
    }
}
void Board::drawTakenFigs(Player& player, int from, int to) {
    std::cout << "\t";
    for (int j = from; j < player.takenFigures.size() && j < to; j++) {
        std::cout << player.takenFigures[j]->getSymb();
        std::cout << " ";
    }
}
void Board::drawPawnProm() {
    if (isPawnProm)
        SetConsoleTextAttribute(console, 7);
    else
        SetConsoleTextAttribute(console, 0);
    std::cout << "    Pawn promotion: ";
    for (int i = 0; i < width; i++)
    {
        if (isPawnProm) {
            if (selectBtnX == i && selectBtnY == 8)
                SetConsoleTextAttribute(console, 112);
            else
                SetConsoleTextAttribute(console, 7);
        }
        else
            SetConsoleTextAttribute(console, 0);
        if (i == 0)
            std::cout << "Q";
        else if (i == 2)
            std::cout << "&";
        else if (i == 4)
            std::cout << "$";
        else if (i == 6)
            std::cout << "I";
        else
            std::cout << " ";
    }
    SetConsoleTextAttribute(console, 7);
}
Board::Board() {}
int Board::getSelectBtnX() const {
    return selectBtnX;
}
int Board::getSelectBtnY() const {
    return selectBtnY;
}
void Board::setSelectBtnX(int x) {
    if (x >= 0 && x < width)
        selectBtnX = x;
}
void Board::setSelectBtnY(int y) {
    if (y >= 0 && y < height)
        selectBtnY = y;
    if (isPawnProm)
        selectBtnY = y;
}
void Board::setPosMoves(std::vector<std::pair<int, int>> posMoves) {
    this->posMoves = posMoves;
}
void Board::setPawnProm() {
    isPawnProm = true;
}
void Board::unsetPawnProm() {
    isPawnProm = false;
}
bool Board::getPawnProm() {
    return isPawnProm;
}
void Board::setResult(GameResult res) {
    result = res;
}
std::vector<std::pair<int, int>>& Board::getPosMoves() {
    return posMoves;
}
void Board::draw(Player& playerOne, Player& playerTwo) {
    std::cout.flush();
    SetConsoleCursorPosition(console, coord);

    std::cout << "\n\n     ";
    for (int i = 65; i < 73; i++)
        std::cout << (char)i;
    std::cout << '\n';
    for (int i = 0; i < height; i++)
    {
        std::cout << "    " << i + 1;
        for (int j = 0; j < width; j++)
        {
            bool isDrawn = false;
            for (auto figure : playerOne.figures)
            {
                if (figure->x == j && figure->y == i) {
                    colorCell(j, i, 112, 128);
                    colorSelectBtn(j, i, 160);
                    colorPosMoves(j, i, 224, 176);
                    std::cout << figure->getSymb();
                    isDrawn = true;
                    break;
                }
            }
            if (isDrawn)
                continue;
            for (auto figure : playerTwo.figures)
            {
                if (figure->x == j && figure->y == i) {
                    colorCell(j, i, 116, 132);
                    colorSelectBtn(j, i, 164);
                    colorPosMoves(j, i, 228, 180);
                    std::cout << figure->getSymb();
                    isDrawn = true;
                    break;
                }
            }
            if (isDrawn)
                continue;
            colorCell(j, i, 116, 132);
            colorSelectBtn(j, i, 164);
            colorPosMoves(j, i, 228, 180);
            std::cout << " ";
        }
        SetConsoleTextAttribute(console, 7);
        std::cout << i + 1;
        if (i == 0) {
            std::cout << "\tPlayer 1 ";
            if (result == GameResult::PlayerOneWins) {
                SetConsoleTextAttribute(console, 10);
                std::cout << "WINS";
                SetConsoleTextAttribute(console, 7);
            }
            else if (result == GameResult::PlayerTwoWins) {
                SetConsoleTextAttribute(console, 12);
                std::cout << "Loses";
                SetConsoleTextAttribute(console, 7);
            }
            else if (result == GameResult::StaleMate) {
                SetConsoleTextAttribute(console, 14);
                std::cout << "STALEMATE";
                SetConsoleTextAttribute(console, 7);
            }
        }
        else if (i == 1)
            drawTakenFigs(playerOne, 0, 6);
        else if (i == 2)
            drawTakenFigs(playerOne, 6, 12);
        else if (i == 3)
            drawTakenFigs(playerOne, 12, 16);
        else if (i == 4) {
            std::cout << "\tPlayer 2 ";
            if (result == GameResult::PlayerOneWins) {
                SetConsoleTextAttribute(console, 12);
                std::cout << "LOSES";
                SetConsoleTextAttribute(console, 7);
            }
            else if (result == GameResult::PlayerTwoWins) {
                SetConsoleTextAttribute(console, 10);
                std::cout << "WINS";
                SetConsoleTextAttribute(console, 7);
            }
            else if (result == GameResult::StaleMate) {
                SetConsoleTextAttribute(console, 14);
                std::cout << "STALEMATE";
                SetConsoleTextAttribute(console, 7);
            }
        }
        SetConsoleTextAttribute(console, 12);
        if (i == 5)
            drawTakenFigs(playerTwo, 0, 6);
        else if (i == 6)
            drawTakenFigs(playerTwo, 6, 12);
        else if (i == 7)
            drawTakenFigs(playerTwo, 12, 16);
        SetConsoleTextAttribute(console, 7);
        std::cout << '\n';
    }
    std::cout << "     ";
    for (int i = 65; i < 73; i++)
        std::cout << (char)i;
    std::cout << '\n';
    std::cout << '\n';
    drawPawnProm();
}