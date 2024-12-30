#include "tree.h"
#include <queue>
#include <algorithm>

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

Tree::Tree(Node* root) : root(root) {}

Tree::~Tree() {
    deleteNode(root);
}

void Tree::deleteNode(Node* node) {
    if (!node) {
        return;
    }

    for (Node* child : node->children) {
        deleteNode(child);
    }

    delete node;
}

bool Tree::dfs(Node* node,
               unordered_set<string>& visited,
               vector<pair<Move, Game*>>& path,
               vector<pair<Move, Game*>>& bestSolution,
               int& solutionsFound,
               int& pathsTried,
               int numIterations)
{
    if (node->game->solved()) {
        solutionsFound++;

        if (bestSolution.empty() || path.size() < bestSolution.size()) {
            bestSolution = path;
        }

        if (solutionsFound >= numIterations) {
            return true;
        }

        return false;
    }

    node->generateChildren();

    for (Node* child : node->children) {
        string stateSig = child->game->signature();
        if (!visited.count(stateSig)) {
            visited.insert(stateSig);

            path.push_back({child->move, child->game});

            bool stopSearch = dfs(child, visited, path, bestSolution, solutionsFound, pathsTried, numIterations);
            if (stopSearch) {
                return true;
            }

            path.pop_back();

            pathsTried++;
            if (pathsTried % 1000 == 0) {
                cout << "Paths tried so far: " << pathsTried << endl;
                cout << "Shortest path: " << bestSolution.size() << endl;
            }
        }
    }

    return false;
}

vector<pair<Move, Game*>> Tree::solve(int numIterations)
{
    if (!root) {
        return {};
    }

    unordered_set<string> visited;
    visited.insert(root->game->signature());

    vector<pair<Move, Game*>> path;

    vector<pair<Move, Game*>> bestSolution;

    int solutionsFound = 0;

    int pathsTried = 0;

    dfs(root, visited, path, bestSolution, solutionsFound, pathsTried, numIterations);

    if (solutionsFound > 0) {
        cout << "Found " << solutionsFound
             << " solutions, returning the shortest one with length "
             << bestSolution.size() << " after trying "
             << pathsTried << " expansions." << endl;
    } else {
        cout << "No solutions found after trying " << pathsTried << " expansions." << endl;
    }

    return bestSolution;
}
