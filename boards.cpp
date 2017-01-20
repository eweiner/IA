#include <iostream>
#include <string>
#include "boards.h"

TBoard::TBoard() {
    boardState = new int*[NUMROWS];
    numMoves = 0;
    for (int r = 0; r < NUMROWS; r++) {
        boardState[r] = new int[NUMCOLUMNS];
        for (int c = 0; c < NUMCOLUMNS; c++) {
            boardState[r][c] = 0;
        }
    }
}

TBoard::TBoard(int** boardState) {
    this->boardState = boardState;
    numMoves = 0;
    for (int r = 0; r < NUMROWS; r++) {
        for (int c = 0; c < NUMCOLUMNS; c++) {
            if (boardState[r][c] != 0) {
                numMoves++;
            }
        }
    }
}

TBoard::~TBoard() {
    for (int i = 0; i < NUMROWS; i++) {
        delete[] boardState[i];
    }
    delete[] boardState;
}

int** TBoard::getBoard() {
    return boardState;
}

int TBoard::getNumMoves() {
    return numMoves;
}

std::string TBoard::numToStr(int num) {
    if (num == 0) {
        return "-";
    }
    std::string toRet = (num == 1) ? "X" : "O";
    return toRet;
}

void TBoard::reset() {
    for (int r = 0; r < NUMROWS; r++) {
        for (int c = 0; c < NUMCOLUMNS; c++) {
            boardState[r][c] = 0;
        }
    }
    numMoves = 0;
}

int TBoard::strToNum(std::string letter) {
    if (letter == "X") {
        return 1;
    } 
    if (letter == "O") {
        return 2;
    }
    return 0;
}

void TBoard::print() {
    for (int i = 0; i < NUMROWS; i++) {
        std::cout << "[ ";
        for (int j = 0; j < NUMCOLUMNS; j++) {
            std::cout << numToStr(boardState[i][j]) << " ";
        }
        std::cout << "]" << std::endl;
    }
}

int TBoard::makeMove(int r, int c, std::string letter) {
    if (r < 3 && r >=0 && c < 3 && c >= 0) {
        if (boardState[r][c] == 0) {
            boardState[r][c] = strToNum(letter);
            numMoves += 1;
            return 0;
        }
    }
    return -1;
}

int TBoard::checkWin() {
    for (int r = 0; r < NUMROWS - 2; r++) {
        for (int c = 0; c < NUMCOLUMNS - 2; c++) {
            if(boardState[r][c] != 0) {
                
                //Horizontal check
                if (boardState[r][c] == boardState[r][c + 1] && boardState[r][c] == boardState[r][c + 2]) {
    //                    std::cout << "Horizontal win in row: " << r << std::endl;
                    return boardState[r][c];
                //Vertical check
                } else if (boardState[r][c] == boardState[r + 1][c] && boardState[r][c] == boardState[r + 2][c]) {
    //                    std::cout << "Vertical win in column: " << c << std::endl;
                    return boardState[r][c];
                //Left to right diagonal
                } else if (boardState[r][c] == boardState[r + 1][c + 1] && boardState[r][c] == boardState[r + 2][c + 2]) {
    //                    std::cout << "Left to right win" << std::endl;
                    return boardState[r][c];
                }
                //Right to left diagonal
            } 
            if (boardState[r][c + 2] == boardState[r + 1][c + 1] && boardState[r][c + 2] == boardState[r + 2][c] && boardState[r][c + 2] != 0) {
    //                    std::cout << "Right to Left win" << std::endl;
                    return boardState[r + 1][c + 1];
            }
                    
            
        }
    }
    return 0;
    
}

bool TBoard::checkValid(int r, int c) {
    if (r >= 0 && r < NUMROWS && c >= 0 && c < NUMCOLUMNS) {
        if (boardState[r][c] == 0) {
            return true;
        }
        return false;
    }
    std::cout << "Move out of bounds" << std::endl;
    return false;
}

void TBoard::undo(int* previousCoordinates) {
    if (previousCoordinates[0] != -1) {
        boardState[previousCoordinates[0]][previousCoordinates[1]] = 0;
    } else {
        std::cout << "Can't undo" << std::endl;
    }
    numMoves--;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
CBoard::CBoard() {
    boardState = new int*[NUMROWS];
    numMoves = 0;
    for (int r = 0; r < NUMROWS; r++) {
        boardState[r] = new int[NUMCOLUMNS];
        for (int c = 0; c < NUMCOLUMNS; c++) {
            boardState[r][c] = 0;
        }
    }
}

CBoard::~CBoard() {
    for (int i = 0; i < NUMROWS; i++) {
        delete[] boardState[i];
    }
    delete[] boardState;
}

std::string CBoard::numToStr(int num) {
    if (num == 1)
        return "r";
    if (num == 2)
        return "b";
    if (num == 0)
        return "-";
    return "";
}

int CBoard::strToNum(std::string letter) {
    if (letter == "r")
        return 1;
    if (letter == "b")
        return 2;
    if (letter == "-")
        return 0;
    return -1;
}

void CBoard::reset() {
    for (int r = 0; r < NUMROWS; r++) {
        for (int c = 0; c < NUMCOLUMNS; c++) {
            boardState[r][c] = 0;
        }
    }
    numMoves = 0;
}

void CBoard::print() {
    std::cout << "  0 1 2 3 4 5 6  " << std::endl;
    for (int i = 0; i < NUMROWS; i++) {
        std::cout << "[ ";
        for (int j = 0; j < NUMCOLUMNS; j++) {
            std::cout << numToStr(boardState[i][j]) << " ";
        }
        std::cout << "]" << std::endl;
    }
}

int CBoard::drop(int c, int color) {
    if (c < NUMCOLUMNS && c >= 0) {
        for (int r = NUMROWS - 1; r >= 0; r--) {
            if (boardState[r][c] == 0) {
                boardState[r][c] = color;
                numMoves++;
                return 0;
            }
        }
    }
    return -1; 
}

int CBoard::checkWin() {
    //Horizontal Check
    for (int r = 0; r < NUMROWS; r++) {
        for (int c = 0; c < NUMCOLUMNS - 3; c++) {
            if (boardState[r][c] != 0) {
                if (boardState[r][c] == boardState[r][c+1] && boardState[r][c] == boardState[r][c+2] &&
                    boardState[r][c] == boardState[r][c+3]) {
                        return boardState[r][c];
                    }
            }
        }
    }
    //Vertical Check
    for (int c = 0; c < NUMCOLUMNS; c++) {
        for (int r = 0; r < NUMROWS - 3; r++) {
            if (boardState[r][c] != 0) {
                if (boardState[r][c] == boardState[r + 1][c] && boardState[r][c] == boardState[r + 2][c] &&
                    boardState[r][c] == boardState[r + 3][c]) {
                        return boardState[r][c];
                    }
            }
        }
    }
    //Left to right check
    for (int r = 0; r < NUMROWS - 3; r++) {
        for (int c = 0; c < NUMCOLUMNS - 3; c++) {
            if (boardState[r][c] != 0) {
                if (boardState[r][c] == boardState[r+1][c+1] && boardState[r][c] == boardState[r+2][c+2] &&
                    boardState[r][c] == boardState[r+3][c+3]) {
                        return boardState[r][c];
                    }
            }
        }
    }
    for (int r = 0; r < NUMROWS - 3; r++) {
        for (int c = NUMCOLUMNS - 1; c >= 3; c--) {
            if (boardState[r][c] != 0) {
                if (boardState[r][c] == boardState[r+1][c-1] && boardState[r][c] == boardState[r+2][c-2] &&
                    boardState[r][c] == boardState[r+3][c-3]) {
                        return boardState[r][c];
                    }
            }
        }
    }
    
    return 0;
}

bool CBoard::checkValid(int c) {
    return (boardState[0][c] == 0 && c >= 0 && c < NUMCOLUMNS);
}

void CBoard::undo(int previousColumn) {
    for (int r = 0; r < NUMROWS; r++) {
        if (boardState[r][previousColumn] > 0) {
            boardState[r][previousColumn] = 0;
            numMoves--;
            break;
        }
    }
    
}