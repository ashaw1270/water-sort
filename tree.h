#ifndef TREE_H
#define TREE_H

#include "game.h"
#include <unordered_set>

class Node {
public:
    Node(Game* game);
    Node(Move move, Game* game);
    
    ~Node();

    void generateChildren();

    friend class Tree;
private:
    Move move;
    Game* game;
    std::vector<Node*> children;
};

class Tree {
public:
    Tree(Node* root);
    ~Tree();

    std::vector<std::pair<Move, Game*>> solve(int numIterations);
private:
    Node* root;
    void deleteNode(Node* node);
    bool dfs(Node* node,
             std::unordered_set<std::string>& visited,
             std::vector<std::pair<Move, Game*>>& path,
             std::vector<std::pair<Move, Game*>>& bestSolution,
             int& solutionsFound,
             int& pathsTried,
             int numIterations);
};

#endif // TREE_H
