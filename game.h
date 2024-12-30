#ifndef GAME_H
#define GAME_H

#include "tube.h"
#include <iostream>
#include <vector>

// pour tube1 into tube2
class Move {
public:
    Move() : Move(-1, -1) {}
    Move(int tube1, int tube2) : tube1(tube1), tube2(tube2) {}

    bool isNull() {
        return tube1 == -1 || tube2 == -1;
    }

    void print() {
        std::cout << "Pour tube " << tube1 << " into tube " << tube2 << std::endl;
    }
private:
    int tube1;
    int tube2;
};

class Game {
public:
    Game(int numTubes);
    Game(int numTubes, Tube* tubes);
    Game(const Game& other);

    ~Game();

    Game* newGame(const string& str);

    std::string signature() const;

    void setTube(int numTube, Tube& tube);

    // pour tube 1 into tube 2
    int pour(int tube1, int tube2);

    bool solved();

    std::vector<std::pair<Move, Game*>> nextGames();

    void print();
private:
    int numTubes;
    Tube* tubes;
};

#endif // GAME_H
