#ifndef AGENTS_H
#define AGENTS_H
#include "boards.h"
#include <vector>



class Tree {
    private:
        int depth;
        double value;
        int nextMoveIndex;
        std::vector<Tree*> children;
        TBoard *board;
        int previousCoordinate[2];
    public:
        int checkThree(int space1, int space2, int space3);
        int numTwos(int player, TBoard *board);
        double theuristic(int computerPlayer, TBoard *board);
        void generateTree(int computerPlayer, int maxDepth, int depth);
        Tree(TBoard *board, int depth, int player);
 //       Tree(int**boardState, int turn, int depth);
        ~Tree();
        void printPath();
        std::vector<Tree*> getChildren(){return children;}
        double getValue() {return value;}
        void setValue(double value) {this->value = value;}
};

class TAgent {
    private:
        Tree *t;
        TBoard *board;
    public:
        bool isCorner(int r, int c);
        TAgent(int computerPlayer, TBoard *emptyBoard);
        ~TAgent();
        int* makeMove();
        void updateBoard(int row, int column, int player, int mover);
        void printValueTree(Tree *t);
        Tree* getTree();
        void reset() {board->reset();}
};


#endif