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
        void generateTree(int computerPlayer, int maxDepth, int depth);
    public:
        int checkThree(int space1, int space2, int space3);
        int numTwos(int player, TBoard *board);
        double theuristic(int computerPlayer, TBoard *board);
        
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
        TAgent(int computerPlayer, TBoard *startingBoard);
        ~TAgent();
        int* makeMove();
        void updateBoard(int row, int column, int player, int mover);
        void printValueTree(Tree *t);
        Tree* getTree();
        void reset() {board->reset();}
};

class CTree {
    private:
        int depth;
        double value;
        int nextMoveIndex;
        std::vector<CTree*> children;
        CBoard *board;
        int previousCoordinate;
        void generateTree(int computerPlayer, int maxDepth, int depth);
    public:
        int check4for3(int space1, int space2, int space3, int space4);
        int check4for2(int space1, int space2, int space3, int space4);
        int numThrees(int player, CBoard *board);
        int numTwos(int player, CBoard *board);
        double cheuristic(int computerPlayer, CBoard *board);
        CTree(CBoard *board, int depth, int player);
        ~CTree();
        std::vector<CTree*> getChildren(){return children;}
        double getValue() {return value;}
        void setValue(double value) {this->value = value;}
};

class CAgent {
    private:
        int color;
        CTree *t;
        CBoard *board;
    public:
        CAgent(int computerPlayer, CBoard *startingBoard);
        ~CAgent();
        int makeMove();
        void updateBoard(int column, int mover);
        void printValueTree(CTree *t);
        CTree* getTree() {return t;}
        void reset();
        int getColor() {return color;}
};
#endif