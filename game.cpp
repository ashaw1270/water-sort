#include "game.h"
#include <iostream>
#include <sstream>
#include <algorithm>

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

Game* newGame(const string& str) {
    vector<Tube> tubeVector;
    stringstream ss(str);
    string color;

    while (!ss.eof()) {
        stack<pair<string, int>> s;
        for (int i = 0; i < 4; i++) {
            ss >> color;
            s.push({color, 1});
        }
        tubeVector.push_back(Tube(s));
    }

    Tube* tubes = new Tube[tubeVector.size()];
    for (size_t i = 0; i < tubeVector.size(); i++) {
        tubes[i] = tubeVector[i];
    }

    return new Game(tubeVector.size(), tubes);
}

string Game::signature() const {
    vector<string> sigs;
    for (int i = 0; i < numTubes; i++) {
        Tube& tube = tubes[i];
        sigs.push_back(tube.signature());
    }

    sort(sigs.begin(), sigs.end());

    stringstream output;
    for (string sig : sigs) {
        output << sig << "|";
    }
    return output.str();
}

void Game::setTube(int numTube, Tube& tube) {
    if (numTube < numTubes) {
        tubes[numTube] = tube;
    }
}

int Game::pour(int t1, int t2) {
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

    return numAdded;
}

bool Game::solved() {
    for (int i = 0; i < numTubes; i++) {
        if (!tubes[i].solved()) {
            return false;
        }
    }
    return true;
}

vector<pair<Move, Game*>> Game::nextGames() {
    vector<pair<Move, Game*>> games;

    for (int i = 0; i < numTubes; i++) {
        for (int j = 0; j < numTubes; j++) {
            if (i == j || tubes[i].solved() || (tubes[i].sameColor() && tubes[j].size() == 0)) {
                continue;
            }

            Game* nextGame = new Game(*this);

            int numOnTop = tubes[i].peek().second;
            int numAdded = nextGame->pour(i, j);
            if (numAdded == numOnTop) {
                Move move(i, j);
                games.push_back({move, nextGame});
            } else {
                delete nextGame;
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
