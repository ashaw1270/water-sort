#ifndef TREE_H
#define TREE_H

#include "game.h"

class Node {
public:
    Node(Game* game);
    Node(Move move, Game* game);
    
    ~Node();

    void generateChildren();
private:
    Move move;
    Game* game;
    std::vector<Node*> children;
};

class Tree {
public:
    Tree(Node* root);
private:
    Node* root;
};

#endif // TREE_H
