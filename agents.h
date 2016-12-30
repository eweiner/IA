#ifndef AGENTS_H
#define AGENTS_H
#include "boards.h"
#include <vector>



class Tree {
    private:
        int value, depth;
        std::vector<Tree*> children;
        TBoard *board;
        int previousCoordinate[2];
    public:
        void generateTree(int computerPlayer);
        Tree(TBoard *board, int depth);
 //       Tree(int**boardState, int turn, int depth);
        ~Tree();
        void printPath();
        std::vector<Tree*> getChildren(){return children;}
        

};


#endif