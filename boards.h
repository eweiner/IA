#include <string>
#include <iostream>
#ifndef BOARDS_H
#define BOARDS_H

class TBoard {
    private:
        int** boardState;
        int numMoves;
    public:
        static const int NUMROWS = 3;
        static const int NUMCOLUMNS = 3;
        TBoard();
        TBoard(int** boardState);
        ~TBoard();
        int** getBoard();
        int getNumMoves();
        std::string numToStr(int num);
        int strToNum(std::string letter);
        void reset();
        void print();
        int makeMove(int r, int c, std::string letter);
        int checkWin();
        bool checkValid(int r, int c);
        void undo(int* previousCoordinates);

        
};

class CBoard {
    private:
        int** boardState;
        int numMoves;
    public:
        static const int NUMROWS = 6;
        static const int NUMCOLUMNS = 7;
        CBoard();
        ~CBoard();
        int** getBoard() {return boardState;}
        int getNumMoves() {return numMoves;}
        std::string numToStr(int num);
        int strToNum(std::string letter);
        void reset();
        void print();
        int drop(int c, int color);
        int checkWin();
        bool checkValid(int c);
        void undo(int previousColumn);
};

#endif