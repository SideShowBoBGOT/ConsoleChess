#pragma once
#include <conio.h>
#include <string.h>
#include "Player.h"
#include "Board.h"
#include "GameResult.h"
class GameLogic
{
private:
	
	bool isPlayerOneTurn = true;
	bool isKingAttacked = false;
	GameResult result = GameResult::UnFinished;
	Figure* selectedFig = nullptr;
	Figure* getKing(Player& player);
	void setPosMoves(Player& player, Player& enemy, Board& board, int selectBtnX, int selectBtnY);
	void pawnPromotion(Player& player, Board& board);
	void Check(Player& player, Player& enemy, Board& board);
	void MateOrStaleMate(Player& player, Player& enemy, Board& board);
	void makeMove(Player& player, Player& enemy, Board& board, int selectBtnX, int selectBtnY);
public:
	GameResult getResult();
	void input(Player& playerOne, Player& playerTwo, Board& board);
	
};

