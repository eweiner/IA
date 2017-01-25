#include <iostream>
#include "boards.h"
#include "agents.h"

void tplayTwoPlayer() {
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

void tplayOnePlayer() {
    using namespace std;
    bool again = true;
    string yon = "";
    TBoard *board = new TBoard();
    TBoard *computerBoard = new TBoard();
    cout << "Initializing computer player" << endl;
    TAgent *computer = new TAgent(1, computerBoard);
    while (again) {
        int row = 0;
        int column = 0;
        int turn = 0;
        int valid = 0;
        int* computerMove;
        board->reset();
        while (board->checkWin() == 0 && board->getNumMoves() < 9) {
            computerMove = computer->makeMove();
            computer->updateBoard(computerMove[0], computerMove[1], 1, 1);
            board->makeMove(computerMove[0], computerMove[1], "X");
            if (board->checkWin() != 0 || board-> getNumMoves() == 9) {
                break;
            }
            board->print();
            while (valid >= 0) {
                cout << board->numToStr(2) <<" Please enter row for move: (0-2) ";
                cin >> row;
                cout << "Please enter column for move: (0-2) ";
                cin >> column;
                valid = board->makeMove(row, column, board->numToStr(2));
                computer->updateBoard(row, column, 1, 2);
                if (valid == -1) {
                    cout << "Please make a valid move" << endl;
                } else {
                    turn = 1 - turn;
                    break;
                }
            }
        }
        board->print();
        if (board->getNumMoves() < 9 || board->checkWin() != 0) {
            cout << "Congratulations: " << board->numToStr(board->checkWin()) << "'s, you win!" << endl;
            cout << "Play again? (y/n) " << endl;
            board->reset();
            computer->reset();
        } else {
            cout << "Stalemate, play again? (y/n) " << endl;
            board->reset();
            computer->reset();
        }
        cin >> yon;
        if (yon == "n") {
            again = false;
        }
    }
    delete computer;
    delete board;
}


void cplayTwoPlayer() {
    using namespace std;
    bool again = true;
    string yon = "";
    CBoard *board = new CBoard();
    while (again) {
        int row = 0;
        int column = 0;
        int turn = 1;
        int valid = 0;
        board->reset();
        while (board->checkWin() == 0 && board->getNumMoves() < 42) {
            board->print();
            cout << "Please enter column for move: (0-6) ";
            cin >> column;
            valid = board->drop(column, turn);
            if (valid == -1) {
                cout << "Please make a valid move" << endl;
            } else {
                turn = 3 - turn;
            }
        }
        board->print();
        if (board->getNumMoves() < 42 || board->checkWin() != 0) {
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

void cplayerOnePlayer() {
    using namespace std;
    bool again = true;
    string yon = "";
    int computerMove;
    CBoard *board = new CBoard();
    CBoard *computerBoard = new CBoard();
    CAgent *computer = new CAgent(1, computerBoard);
    while (again) {
        int row = 0;
        int column = 0;
        int turn = 1;
        int valid = 0;
        board->reset();
        while (board->checkWin() == 0 && board->getNumMoves() < 42) {
            computerMove = computer->makeMove();
            computer->updateBoard(computerMove, computer->getColor());
            board->drop(computerMove, computer->getColor());
            if (board->checkWin() != 0 || board-> getNumMoves() == 42) {
                break;
            }
            board->print();
            cout << "Please enter column for move: (0-6) ";
            cin >> column;
            valid = board->drop(column, 2);
            while (valid == -1) {
                cout << "Please make a valid move" << endl;
                cout << "Please enter column for move: (0-6) ";
                cin >> column;
                valid = board->drop(column, 2);
            }
            computer->updateBoard(column, 2);
        }
        board->print();
        if (board->getNumMoves() < 42 && board->checkWin() != 0) {
            cout << "Congratulations: " << board->numToStr(board->checkWin()) << "'s, you win!" << endl;
            cout << "Play again? (y/n) " << endl;
            board->reset();
            computer->reset();
        } else {
            cout << "Stalemate, play again? (y/n) " << endl;
            board->reset();
            computer->reset();
        }
        cin >> yon;
        if (yon == "n") {
            again = false;
        }
    }
    delete computer;
    delete computerBoard;
    delete board;
}

int main() {
    cplayerOnePlayer();
//    CBoard *board = new CBoard();
//    CTree *t = new CTree(board, 0, 1);

//    delete t;
//    cplayTwoPlayer();

//    tplayOnePlayer();
/* Test code for TTT
            TBoard *board = new TBoard();
            TAgent *computerPlayer = new TAgent(1, board);
            computerPlayer->updateBoard(0,0,1,1);
            computerPlayer->updateBoard(0,1,1,2);
            computerPlayer->updateBoard(0,2,1,1);
            computerPlayer->updateBoard(1,0,1,2);
            computerPlayer->updateBoard(1,1,1,1);
            computerPlayer->updateBoard(1,2,1,2);
            board->print();
        //    std::cout << computerPlayer->makeMove()[1];


            TBoard *board = new TBoard();
            TAgent *computerPlayer = new TAgent(1, board);
        //    computerPlayer->printValueTree(computerPlayer->getTree());
            Tree *t = computerPlayer->getTree();
            std::cout << t->getChildren().size();
            for (int i = 0; i < t->getChildren().size(); i++) {
                std::cout << "|" << t->getChildren()[i]->getValue() << "|";
        //        for (int j = 0; j < t->getChildren()[i]->getChildren().size(); j++) {
        //            std::cout << " " << t->getChildren()[i]->getChildren()[j]->getValue() << " ";
        //           for (int k = 0; k < t->getChildren()[i]->getChildren()[j]->getChildren().size(); k++) {
        //               std::cout << " " << t->getChildren()[i]->getChildren()[j]->getChildren()[k]->getValue() << " ";
        //           }
        //           std::cout << std::endl;
        //       }
                
        //       std::cout << std::endl;
            }
            

            
        //    playOnePlayer();

        /*
            TBoard *board = new TBoard();
        //    Tree *t = new Tree(board, 0, 1);
            TBoard *computerBoard = new TBoard();
            TAgent *computerPlayer = new TAgent(1, computerBoard);
            std::cout << "Row of move " << computerPlayer->makeMove()[0] << std::endl;
            std::cout << "Column of move " << computerPlayer->makeMove()[1] << std::endl;
            computerPlayer->updateBoard(0, 0, 1);
            board->makeMove(0, 0, "X");
            board->print();
            

        //    delete t;
            delete computerPlayer;
            delete board;
        //    delete board;
*/
}