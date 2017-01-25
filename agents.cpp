#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "agents.h"
#include "boards.h"

/*
 Checks if there are 2 of the same type with an empty space in the middle
*/
int Tree::checkThree(int space1, int space2, int space3) {
    if (space1 == space2 && space3 == 0 && space1 != 0) {
        return space1;
    }
    if (space2 == space3 && space1 == 0 && space2 != 0) {
        return space2;
    }
    if (space1 == space3 && space2 == 0 && space1 != 0) {
        return space1;
    }
    return 0;
}

/*
 Returns how many two in a rows there are for a given player
*/
int Tree::numTwos(int player, TBoard *board) {
    int num_two_in_a_row = 0;
    for (int i = 0; i < board->NUMROWS; i++) {
        if (checkThree(board->getBoard()[i][0], board->getBoard()[i][1], board->getBoard()[i][2]) == player) {
            num_two_in_a_row++;
        }
        if (checkThree(board->getBoard()[0][i], board->getBoard()[1][i], board->getBoard()[2][i]) == player) {
            num_two_in_a_row++;
        }
        
    }
    if (checkThree(board->getBoard()[0][0], board->getBoard()[1][1], board->getBoard()[2][2]) == player) {
            num_two_in_a_row++;
        }
    if (checkThree(board->getBoard()[0][2], board->getBoard()[1][1], board->getBoard()[2][0]) == player) {
        num_two_in_a_row++;
    }
    return num_two_in_a_row;
}

/*
 Proprietary algorithm
*/
double Tree::theuristic(int computerPlayer, TBoard *board) {
    int** boardState = board->getBoard();
    int score = 0;
    if (board->checkWin() == computerPlayer) {
        score = +1000.0;
    } else if (board->checkWin() != 0 && board->checkWin() != computerPlayer) {
        score += -1000.0;
    } else if (board->getNumMoves() == 9) {
        score += 0.0;
    }
    if (numTwos(3 - computerPlayer, board) > 1) {
        score += -500.0;
    }
    if (numTwos(3 - computerPlayer, board) == 1) {
        score += -25.0;
    }
    if (numTwos(computerPlayer, board) > 1) {
        score += 500.0;
    }
    if (numTwos(computerPlayer, board) == 1) {
        score += 25.0;
    }
    return score;
    /*else {
        for (int r = 0; r < board->NUMROWS - 1; r++) {
            for (int c = 0; c < board->NUMCOLUMNS - 1; c++) {
                if (boardState[r][c] == boardState[r+1][c]) {
                    num_two_in_a_row++;
                }
                if (boardState[r][c] == )
            }
        }
    }
    */
}

/*
    * Recursively generates a tree of possible moves and scores based on minimax
    !!!!!!!!!!!!!!!!!!!! Possibly use depth from high to low instead of from 0 !!!!!!!!!!!!!!!!!!!!
    *for each row in board:
    For each column in row:
    If the move is valid:
        if !(win or tie or loss):
            children.append(new Tree(board with move))
        else:
            score()
    undo()
*/
void Tree::generateTree(int computerPlayer, int maxDepth, int depth) {



    std::string turn = board->getNumMoves() % 2 == 0 ? "X" : "O";
    for (int r = 0; r < board->NUMROWS; r++) {
        for (int c = 0; c < board->NUMCOLUMNS; ++c) {
            if(board->checkValid(r, c)) {
                board->makeMove(r,c, turn);
                previousCoordinate[0] = r;
                previousCoordinate[1] = c;
                

                
              if (depth < maxDepth) {
                    children.push_back(new Tree(board, depth + 1, computerPlayer));
                    if (board->checkWin() > 0 || board->getNumMoves() == 9)
                        value = theuristic(computerPlayer, board);
                } else {
                    value = theuristic(computerPlayer, board);

                }
                board->undo(previousCoordinate); 
            }
        }
    }
    if (children.size() > 0) {
        
        if (computerPlayer == board->strToNum(turn)) {
            nextMoveIndex = 0;
            for (int i = 0; i < children.size(); i++) {
                if (children[i]->getValue() > children[nextMoveIndex]->getValue()) {
                    nextMoveIndex = i;
                    value = children[i]->getValue();
                }
            }
        } else {
            nextMoveIndex = 0;
            for (int i = 0; i < children.size(); i++) {
                if (children[i]->getValue() < children[nextMoveIndex]->getValue()) {
                    nextMoveIndex = i;
                    value = children[i]->getValue();
                }
            }
        }
        
    }
//    std::cout << "My value is: " << value << std::endl;
    
}

/*
 Construct possibility tree of a given depth (even number)
*/
Tree::Tree(TBoard *board, int depth, int player) {
    this->board = board;
    this->depth = depth;
    generateTree(player, 6, depth);
    
    
    
    
}

Tree::~Tree() {
  //    delete board;
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



TAgent::TAgent(int computerPlayer, TBoard *startingBoard) {
    board = startingBoard;
    t = new Tree(startingBoard, 0, 1);
}

TAgent::~TAgent() {
    delete t;
}

bool TAgent::isCorner(int r, int c) {
    if ((r == 0 && c == 0) || (r == 2 && c == 2) || (r == 0 && c == 2) || (r == 2 && c == 0)) {
        return true;
    }
    return false;
}

int* TAgent::makeMove() {
    int maxIndex = 0;
    int currentIndex = 0;
    std::vector<int> possibleMoves;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board->checkValid(r,c)) {
                possibleMoves.push_back(3*r+c);
 /*
                if (isCorner(r, c) || (r == 1 && c == 1)) {
                    t->getChildren()[currentIndex]->setValue(t->getChildren()[currentIndex]->getValue() + 0.05);
                    currentIndex++;
                }
 */
            }
        }
    }

    for (int i = 1; i < t->getChildren().size(); i++) {
        if (t->getChildren()[i]->getValue() > t->getChildren()[maxIndex]->getValue()) {
            maxIndex = i;
        }
    }
    int* toReturn = new int[2];
    toReturn[0] = possibleMoves[maxIndex] / 3;
    toReturn[1] = possibleMoves[maxIndex] % 3;
    return toReturn;
}

void TAgent::updateBoard(int row, int column, int player, int mover) {
    this->board->makeMove(row, column, this->board->numToStr(mover));
    delete this->t;
    t = new Tree(this->board, 0, player);
}

void TAgent::printValueTree(Tree *t) {
    if (t->getChildren().size() == 0) {
        std::cout << " " << t->getValue() << " ";
    }
    for (int i = 0; i < t->getChildren().size(); i++) {
        printValueTree(t->getChildren()[i]);
    }
    std::cout << " " << t->getValue() << " " << std::endl;
}

Tree* TAgent::getTree() {
    return t;
}

int CTree::check4for3(int space1, int space2, int space3, int space4) {
    if (space1 == space2 && space2 == space3 && space1 != 0 && space4 == 0) {
        return space1;
    }
    if (space2 == space3 && space3 == space4 && space2 != 0 && space1 == 0) {
        return space2;
    }
    if (space1 == space3 && space3 == space4 && space1 != 0 && space2 == 0) {
        return space1;
    }
    if (space1 == space2 && space2 == space4 && space1 != 0 && space3 == 0) {
        return space1;
    }
    return 0;
}

int CTree::check4for2(int space1, int space2, int space3, int space4) {
    if (space1 == space2 && space3 == space4 && space1 != 0 && space3 == 0) {
        return space1;
    }
    if (space2 == space3 && space1 == space4 && space2 != 0 && space1 == 0) {
        return space2;
    }
    if (space3 == space4 && space1 == space2 && space3 != 0 && space1 == 0) {
        return space3;
    }
    if (space1 == space4 && space2 == space3 && space1 != 0 && space2 == 0) {
        return space1;
    }
    if (space1 == space3 && space2 == space4 && space1 != 0 && space4 == 0) {
        return space1;
    }
    if (space2 == space4 && space1 == space3 && space2 != 0 && space1 == 0) {
        return space2;
    }
    return 0;

}

int CTree::numThrees(int player, CBoard *board) {
    int numThrees = 0;
    int** boardState = board->getBoard();
    //Horizontal Check
    for (int r = 0; r < board->NUMROWS; r++) {
        for (int c = 0; c < board->NUMCOLUMNS - 3; c++) {
            if (check4for3(boardState[r][c], boardState[r][c + 1], boardState[r][c + 2], 
                boardState[r][c + 3]) == player) {
                    numThrees++;
                }
        }
    }
    //Vertical Check
    for (int c = 0; c < board->NUMCOLUMNS; c++) {
        for (int r = 0; r < board->NUMROWS - 3; r++) {
            if (check4for3(boardState[r][c], boardState[r + 1][c], boardState[r + 2][c], 
                boardState[r + 3][c]) == player) {
                    numThrees++;
                }
        }
    }
    //Left to right check
    for (int r = 0; r < board->NUMROWS - 3; r++) {
        for (int c = 0; c < board->NUMCOLUMNS - 3; c++) {
            if (check4for3(boardState[r][c], boardState[r + 1][c + 1], boardState[r + 2][c + 2], 
                boardState[r + 3][c + 3]) == player) {
                    numThrees++;
                }
        }
    }

    for (int r = 0; r < board->NUMROWS - 3; r++) {
        for (int c = board->NUMCOLUMNS - 1; c >= 3; c--) {
            if (check4for3(boardState[r][c], boardState[r + 1][c - 1], boardState[r + 2][c - 2], 
                boardState[r + 3][c - 3]) == player) {
                    numThrees++;
                }
        }
    }
    
    return numThrees;

}

int CTree::numTwos(int player, CBoard *board) {
    int** boardState = board->getBoard();
    int numTwos = 0;
    //Horizontal Check
    for (int r = 0; r < board->NUMROWS; r++) {
        for (int c = 0; c < board->NUMCOLUMNS - 3; c++) {
            if (check4for2(boardState[r][c], boardState[r][c + 1], boardState[r][c + 2], 
                boardState[r][c + 3]) == player) {
                    numTwos++;
                }
        }
    }
    //Vertical Check
    for (int c = 0; c < board->NUMCOLUMNS; c++) {
        for (int r = 0; r < board->NUMROWS - 3; r++) {
            if (check4for2(boardState[r][c], boardState[r + 1][c], boardState[r + 2][c], 
                boardState[r + 3][c]) == player) {
                    numTwos++;
                }
        }
    }
    //Left to right check
    for (int r = 0; r < board->NUMROWS - 3; r++) {
        for (int c = 0; c < board->NUMCOLUMNS - 3; c++) {
            if (check4for2(boardState[r][c], boardState[r + 1][c + 1], boardState[r + 2][c + 2], 
                boardState[r + 3][c + 3]) == player) {
                    numTwos++;
                }
        }
    }

    for (int r = 0; r < board->NUMROWS - 3; r++) {
        for (int c = board->NUMCOLUMNS - 1; c >= 3; c--) {
            if (check4for2(boardState[r][c], boardState[r + 1][c - 1], boardState[r + 2][c - 2], 
                boardState[r + 3][c - 3]) == player) {
                    numTwos++;
                }
        }
    }
    
    return numTwos;
}

double CTree::cheuristic(int computerPlayer, CBoard *board) {
    double score = 0;
    if (board->checkWin() == computerPlayer) {
        score = 11000.0;
    } else if (board->checkWin() != 0 && board->checkWin() != computerPlayer) {
        score += -10000.0;
    } else if (board->getNumMoves() == 42) {
        score += 0.0;
    } 
        score += (numTwos(computerPlayer, board));
        score -= (numTwos(3 - computerPlayer, board));
        score += (numThrees(computerPlayer, board) * 100);
        score -= (numThrees(3 - computerPlayer, board) * 100);
    return score;
}
CTree::CTree(CBoard *board, int depth, int player) {
    this->board = board;
    this->depth = depth;
    generateTree(player, 4, depth);
}

CTree::~CTree() {
    children.clear();
}

/*
double CTree::mistakeProbability(int length, double lastProbability) {
    if (length == 1)
        return lastProbability;
    return mistakeProbability((length - 1), (lastProbability/2));
}
void CTree::orderChildren() {
    CTree *tmp;
    for (int i = 0; i < children.size(); i++) {
        int minIndex = i;
        for (int j = i; j < children.size; j++) {
            if (children[j]->getValue() < children[minIndex]->getValue()) {
                minIndex = j;
            }
        }
        tmp = children[i];
        children[i] = children[minIndex];
        children[minIndex] = tmp;
    }
}
*/
void CTree::generateTree(int computerPlayer, int maxDepth, int depth) {
    int turn = board->getNumMoves() % 2 + 1;
    for (int c = 0; c < board->NUMCOLUMNS; ++c) {
        if(board->checkValid(c)) {
            board->drop(c, turn);
            previousCoordinate = c;
            if (depth < maxDepth) {
                children.push_back(new CTree(board, depth + 1, computerPlayer));
                if (board->checkWin() > 0 || board->getNumMoves() == 42)
                    value = cheuristic(computerPlayer, board);
            } else {
                value = cheuristic(computerPlayer, board);

            }
            board->undo(previousCoordinate); 
        }
    }
    
    if (children.size() > 0) {
  //      orderChildren();
       if (computerPlayer == turn) {
            nextMoveIndex = 0;
            for (int i = 0; i < children.size(); i++) {
                if (children[i]->getValue() > children[nextMoveIndex]->getValue()) {
                    nextMoveIndex = i;
                    value = children[i]->getValue();
                }
            }
        } else {
  //            std::vector<double> probabilities;

            nextMoveIndex = 0;
            for (int i = 0; i < children.size(); i++) {
                if (children[i]->getValue() < children[nextMoveIndex]->getValue()) {
                    nextMoveIndex = i;
                    value = children[i]->getValue();
                }
            }
        }
        
    }

}

CAgent::CAgent(int computerPlayer, CBoard *startingBoard) {
    color = computerPlayer;
    board = startingBoard;
    t = new CTree(startingBoard, 0, computerPlayer);
}

CAgent::~CAgent() {
    delete t;
}

int CAgent::makeMove() {
    srand (time(NULL));
    int maxIndex = 0;
    int currentIndex = 0;
    std::vector<int> possibleMoves;
    for (int c = 0; c < board->NUMCOLUMNS; c++) {
        if (board->checkValid(c)) {
            possibleMoves.push_back(c);
 /*
                if (isCorner(r, c) || (r == 1 && c == 1)) {
                    t->getChildren()[currentIndex]->setValue(t->getChildren()[currentIndex]->getValue() + 0.05);
                    currentIndex++;
                }
 */
            }
        }
    
    std::vector<int> maxValueMoves;
    int currentMax = t->getChildren()[0]->getValue();
    int currentValue;
    maxValueMoves.push_back(possibleMoves[0]);
    for (int i = 1; i < t->getChildren().size(); i++) {
        currentValue = t->getChildren()[i]->getValue();
        if (t->getChildren()[i]->getValue() == t->getChildren()[maxIndex]->getValue() && maxIndex != i) {
            maxValueMoves.push_back(possibleMoves[i]);
        }
        if (t->getChildren()[i]->getValue() > t->getChildren()[maxIndex]->getValue()) {
            currentMax = t->getChildren()[i]->getValue();
            maxValueMoves.clear();
            maxValueMoves.push_back(possibleMoves[i]);
            maxIndex = i;
            i = 0;
        }
    }
    int column;

    /* initialize random seed: */
    
    /* generate secret number between 1 and 10: */
    std::cout << maxValueMoves.size() << std::endl;
    int finalIndex = rand() % maxValueMoves.size();
    column = maxValueMoves[finalIndex];
    return column;
}

void CAgent::updateBoard(int column, int mover) {
    board->drop(column, mover);
    delete t;
    t = new CTree(board, 0, color);
}

void CAgent::reset() {
    board->reset();
    delete t;
    t = new CTree(board, 0, color);
}