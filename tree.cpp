#include "tree.h"

using namespace std;

// used only for root node
Node::Node(Game* game) : game(game) {}

Node::Node(Move move, Game* game) : move(move), game(game) {}

Node::~Node() {
    delete game;
}

void Node::generateChildren() {
    vector<pair<Move, Game*>> nextGames = game->nextGames();
    for (pair<Move, Game*> g : nextGames) {
        children.push_back(new Node(g.first, g.second));
    }
}
