#pragma once
#include <Windows.h>
#include <iostream>
#include "Player.h"
#include "GameResult.h"

class Board {
private:
    int width = 8;
    int height = 8;
    int selectBtnX = 0;
    int selectBtnY = 0;
    bool isPawnProm = false;
    GameResult result = GameResult::UnFinished;
    std::vector<std::pair<int, int>> posMoves;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    void colorCell(int x, int y, int colorOne, int colorTwo);
    void colorSelectBtn(int x, int y, int color);
    void colorPosMoves(int x, int y, int colorOne, int colorTwo);
    void drawTakenFigs(Player& player, int from, int to);
    void drawPawnProm();
public:
    Board();
    int getSelectBtnX() const;
    int getSelectBtnY() const;
    void setSelectBtnX(int x);
    void setSelectBtnY(int y);
    void setPosMoves(std::vector<std::pair<int, int>> posMoves);
    void setPawnProm();
    void unsetPawnProm();
    bool getPawnProm();
    void setResult(GameResult res);
    std::vector<std::pair<int, int>>& getPosMoves();
    void draw(Player& playerOne, Player& playerTwo);
   
};
;

