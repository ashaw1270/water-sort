#include "game.h"
#include <iostream>

using namespace std;

Game::Game(int numTubes) : Game(numTubes, new Tube[numTubes]) {}

Game::Game(int numTubes, Tube* tubes) : numTubes(numTubes), tubes(tubes) {}

Game::Game(const Game& other) : Game(other.numTubes) {
    for (int i = 0; i < numTubes; i++) {
        tubes[i] = other.tubes[i];
    }
}

Game::~Game() {
    delete [] tubes;
}

void Game::setTube(int numTube, Tube& tube) {
    if (numTube < numTubes) {
        tubes[numTube] = tube;
    }
}

bool Game::pour(int t1, int t2) {
    if (t1 < 0 || t2 >= numTubes) {
        return false;
    }

    Tube& tube1 = tubes[t1];
    Tube& tube2 = tubes[t2];

    if (tube1.size() == 0) {
        return false;
    }

    pair<string, int> tube1Top = tube1.peek();
    int numAdded = tube2.add(tube1Top);
    tube1.remove(numAdded);

    return numAdded > 0;
}

vector<pair<Move, Game*>> Game::nextGames() {
    vector<pair<Move, Game*>> games;

    for (int i = 0; i < numTubes; i++) {
        for (int j = 0; j < numTubes; j++) {
            if (i == j) {
                continue;
            }

            Game* nextGame = new Game(*this);

            bool validPour = nextGame->pour(i, j);
            if (validPour) {
                Move move(i, j);
                games.push_back({move, nextGame});
            }
        }
    }

    return games;
}

void Game::print() {
    for (int i = 0; i < numTubes; i++) {
        cout << "Tube " << i << ": " << endl;
        tubes[i].print();
        cout << endl;
    }
}
