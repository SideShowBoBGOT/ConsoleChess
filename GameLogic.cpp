#include "GameLogic.h"
GameResult GameLogic::getResult() {
	return result;
}
void GameLogic::input(Player& playerOne, Player& playerTwo, Board& board) {
	char key = _getch();
	int selectBtnX = board.getSelectBtnX();
	int selectBtnY = board.getSelectBtnY();
	if (!board.getPawnProm()) {
		switch (key) {
		case 'w': case 'W':
			board.setSelectBtnY(selectBtnY - 1);
			break;
		case 's': case 'S':
			board.setSelectBtnY(selectBtnY + 1);
			break;
		case 'a': case 'A':
			board.setSelectBtnX(selectBtnX - 1);
			break;
		case 'd': case 'D':
			board.setSelectBtnX(selectBtnX + 1);
			break;
		case 'j': case 'J':
			if (isPlayerOneTurn)
				setPosMoves(playerOne, playerTwo, board, selectBtnX, selectBtnY);
			else
				setPosMoves(playerTwo, playerOne, board, selectBtnX, selectBtnY);
			break;
		case 'k': case 'K':
			if (isPlayerOneTurn)
				makeMove(playerOne, playerTwo, board, selectBtnX, selectBtnY);
			else
				makeMove(playerTwo, playerOne, board, selectBtnX, selectBtnY);
			break;
		default:
			break;
		}
	}
	else {
		Player& player = (isPlayerOneTurn) ? playerTwo : playerOne;
		Figure* promPawn = nullptr;
		switch (key) {
		case 'a': case 'A':
			board.setSelectBtnX(selectBtnX - 2);
			break;
		case 'd': case 'D':
			board.setSelectBtnX(selectBtnX + 2);
			break;
		case 'k': case 'K':

			switch (selectBtnX) {
			case 0:
				promPawn = new Queen(selectedFig->x, selectedFig->y);
				break;
			case 2:
				promPawn = new Bishop(selectedFig->x, selectedFig->y);
				break;
			case 4:
				promPawn = new Knight(selectedFig->x, selectedFig->y);
				break;
			case 6:
				promPawn = new Rook(selectedFig->x, selectedFig->y);
				break;
			}
			for (auto i = begin(player.figures); i != end(player.figures); i++)
			{
				if ((*i) == selectedFig) {
					player.figures.erase(i);
					player.figures.push_back(promPawn);
					break;
				}
			}
			board.unsetPawnProm();
			board.setSelectBtnX(selectedFig->x);
			board.setSelectBtnY(selectedFig->y);
			break;
		default:
			break;
		}
	}
	if (result != GameResult::UnFinished) {
		board.setResult(result);
	}
}
Figure* GameLogic::getKing(Player& player) {
	for (const auto fig : player.figures)
	{
		if (!strcmp(typeid(*fig).name(), typeid(King).name())) {
			return fig;
		}
	}
	return nullptr;
}
void GameLogic::setPosMoves(Player& player, Player& enemy, Board& board, int selectBtnX, int selectBtnY) {
	board.setPosMoves(std::vector<std::pair<int, int>>());
	for (const auto figure : player.figures)
	{
		if (selectBtnX == figure->x && selectBtnY == figure->y) {
			selectedFig = figure;
			board.setPosMoves(player.getPosMoves(figure, enemy));
			break;
		}
	}
}
void GameLogic::pawnPromotion(Player& player, Board& board) {
	if (!strcmp(typeid(*selectedFig).name(), typeid(Pawn).name())) {
		if (reinterpret_cast<Pawn*>(selectedFig)->getDirection() == 'u' && selectedFig->y == 0)
			board.setPawnProm();
		if (reinterpret_cast<Pawn*>(selectedFig)->getDirection() == 'd' && selectedFig->y == 7)
			board.setPawnProm();
		if (board.getPawnProm()) {
			board.setSelectBtnX(0);
			board.setSelectBtnY(8);
		}
	}
}
void GameLogic::Check(Player& player, Player& enemy, Board& board) {
	Figure* enemyKing = getKing(enemy);
	for (const auto& f : player.figures)
	{
		for (const auto& p : player.getPosMoves(f, enemy))
		{
			if (enemyKing->x == p.first && enemyKing->y == p.second) {
				isKingAttacked = true;
				return;
			}
		}
	}
	isKingAttacked = false;
}
void GameLogic::MateOrStaleMate(Player& player, Player& enemy, Board& board) {
	for (const auto& fig : enemy.figures) {
		auto moves = enemy.getPosMoves(fig, player);
		if (!moves.empty())
			return;
	}
	if (isKingAttacked) {
		if (isPlayerOneTurn)
			result = GameResult::PlayerOneWins;
		else
			result = GameResult::PlayerTwoWins;
	}
	else
		result = GameResult::StaleMate;
}
void GameLogic::makeMove(Player& player, Player& enemy, Board& board, int selectBtnX, int selectBtnY) {
	isKingAttacked = false;
	std::vector<std::pair<int, int>>& posMoves = board.getPosMoves();
	for (const auto& pos : posMoves)
	{
		if (selectBtnX == pos.first && selectBtnY == pos.second) {
			for (auto i = begin(enemy.figures); i < end(enemy.figures); i++) {
				if ((*i)->x == selectBtnX && (*i)->y == selectBtnY) {
					player.takenFigures.push_back(*i);
					enemy.figures.erase(i);
					break;
				}
			}
			Figure* king = getKing(player);
			//castling
			if (!strcmp(typeid(*selectedFig).name(), typeid(Rook).name()) &&
				king->x == selectBtnX && king->y == selectBtnY) {
				king->setMoved();
				if (selectedFig->x == 0) {
					selectedFig->x = 2;
					king->x = 1;
				}
				else if (selectedFig->x == 7) {
					selectedFig->x = 4;
					king->x = 5;
				}
			}
			else {
				selectedFig->x = selectBtnX;
				selectedFig->y = selectBtnY;
				pawnPromotion(player, board);
				Check(player, enemy, board);
			}
			selectedFig->setMoved();
			posMoves.clear();
			MateOrStaleMate(player, enemy, board);
			isPlayerOneTurn = !isPlayerOneTurn;
			break;
		}
	}
}