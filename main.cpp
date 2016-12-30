#include <iostream>
#include "boards.h"
#include "agents.h"

void playTwoPlayer() {
    using namespace std;
    bool again = true;
    string yon = "";
    TBoard *board = new TBoard();
    while (again) {
        int row = 0;
        int column = 0;
        int turn = 0;
        int valid = 0;
        board->reset();
        while (board->checkWin() == 0 && board->getNumMoves() < 9) {
            board->print();
            cout << board->numToStr(turn + 1) <<" Please enter row for move: (0-2) ";
            cin >> row;
            cout << "Please enter column for move: (0-2) ";
            cin >> column;
            valid = board->makeMove(row, column, board->numToStr(turn + 1));
            if (valid == -1) {
                cout << "Please make a valid move" << endl;
            } else {
                turn = 1 - turn;
            }
        }
        board->print();
        if (board->getNumMoves() < 9 || board->checkWin() != 0) {
            cout << "Congratulations: " << board->numToStr(board->checkWin()) << "'s, you win!" << endl;
            cout << "Play again? (y/n) " << endl;
            board->reset();
        } else {
            cout << "Stalemate, play again? (y/n) " << endl;
            board->reset();
        }
        cin >> yon;
        if (yon == "n") {
            again = false;
        }
    }
    delete board;
}

int main() {
    TBoard *board = new TBoard();
    Tree *t = new Tree(board, 0);
//    t->printPath();
//    delete t;
}