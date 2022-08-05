#pragma once
#include <iostream>
#include "Player.h"
#include "Board.h"
#include "GameLogic.h"
#include "GameResult.h"
class Game {
private:
    Player playerOne;
    Player playerTwo;
    GameLogic gameLogic;
    Board board;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
public:
    void mainMenu();
    bool rematch();
    void start();
};

