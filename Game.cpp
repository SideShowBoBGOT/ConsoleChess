#include "Game.h"
void Game::mainMenu() {

    int pos = 0;
    for (;;)
    {
        std::cout.flush();
        SetConsoleCursorPosition(console, coord);

        std::cout << "\n\t" << "Menu" << "\n\n";
        for (int i = 0; i < 2; i++)
        {
            std::cout << '\t';
            if (pos == i)
                SetConsoleTextAttribute(console, 12);
            if (i == 0)
                std::cout << "Start";
            else if (i == 1)
                std::cout << "Exit";
            SetConsoleTextAttribute(console, 7);
            std::cout << '\n';
        }
        char key = _getch();
        switch (key) {
        case 'w': case 'W':
            if (pos > 0)
                pos--;
            break;
        case 's': case 'S':
            if (pos < 1)
                pos++;
            break;
        case 'k': case 'K':
            if (pos == 0) {
                do {
                    system("cls");
                    start();
                } while (rematch());
                system("cls");
            }
            else if (pos == 1)
                return;
            break;
        default:
            break;
        }

    }
}
bool Game::rematch() {
    int pos = 0;
    while (true) {
        board.draw(playerOne, playerTwo);

        std::cout << "\n    " << "Rematch?" << "\n\n";

        for (int i = 0; i < 2; i++)
        {
            std::cout << "    ";
            if (pos == i)
                SetConsoleTextAttribute(console, 12);
            if (i == 0)
                std::cout << "Yes";
            else if (i == 1)
                std::cout << "No";
            SetConsoleTextAttribute(console, 7);
        }
        char key = _getch();
        switch (key) {
        case 'a': case 'A':
            if (pos > 0)
                pos--;
            break;
        case 'd': case 'D':
            if (pos < 1)
                pos++;
            break;
        case 'k': case 'K':
            if (pos == 0)
                return true;
            else if (pos == 1)
                return false;
            break;
        default:
            break;
        }
    }
}
void Game::start() {
    playerOne = Player(1);
    playerTwo = Player(2);
    board = Board();
    gameLogic = GameLogic();
    for (;;) {
        board.draw(playerOne, playerTwo);
        gameLogic.input(playerOne, playerTwo, board);
        if (gameLogic.getResult() != GameResult::UnFinished) {
            board.draw(playerOne, playerTwo);
            return;
        }
    }
}