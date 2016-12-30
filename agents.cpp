#include <vector>
#include <algorithm>
#include "agents.h"
#include "boards.h"

void Tree::generateTree(int computerPlayer) {
/*
For each row in board:
    For each column in row:
    If the move is valid:
        if !(win or tie or loss):
            children.append(new Tree(board with move))
        else:
            score()
undo()


void Tree::generateTree(int computerPlayer) {
*/

    std::string turn = board->getNumMoves() % 2 == 0 ? "X" : "O";
    for (int r = 0; r < board->NUMROWS; r++) {
        for (int c = 0; c < board->NUMCOLUMNS; ++c) {
            if(board->checkValid(r, c)) {
                board->makeMove(r,c, turn);
                previousCoordinate[0] = r;
                previousCoordinate[1] = c;
                
                board->print();
                std::cout << " Depth at: " << depth << std::endl;
                std::cout << std::endl;
                
                if(board->checkWin() > 0 || board->getNumMoves() == 9) {
                    if (board->checkWin() == computerPlayer) {
                        value = 1;
                    } else if (board->checkWin() != 0 && board->checkWin() != computerPlayer) {
                        value = -1;
                    } else {
                        value = 0;
                    }
                    
                } else if (depth < 4) {
                    children.push_back(new Tree(board, depth + 1));
                }
                board->undo(previousCoordinate); 
            }
        }
    }
    
}
//Depth first search
// Copy board to new object, doesn't work as all point to same board...'
//Pass TBoard?
Tree::Tree(TBoard *board, int depth) {
    this->board = board;
    this->depth = depth;
    generateTree(1);
    
    
    
    
}

Tree::~Tree() {
    delete board;
    children.clear();
    
}

void Tree::printPath() {
    board->print();
    if (children.size() != 0) {
        std::cout << "Going down!" << std::endl;
        children[0]->printPath();
    } 
    std::cout << "\n";
}
