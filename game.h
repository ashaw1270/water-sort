#ifndef GAME_H
#define GAME_H

#include "tube.h"
#include <vector>

// pour tube1 into tube2
struct Move {
    Move() : Move(-1, -1) {}
    Move(int tube1, int tube2) : tube1(tube1), tube2(tube2) {}

    bool isNull() {
        return tube1 == -1 || tube2 == -1;
    }

    int tube1;
    int tube2;
};

class Game {
public:
    Game(int numTubes);
    Game(int numTubes, Tube* tubes);
    Game(const Game& other);

    ~Game();

    void setTube(int numTube, Tube& tube);

    // pour tube 1 into tube 2
    bool pour(int tube1, int tube2);

    std::vector<std::pair<Move, Game*>> nextGames();

    void print();
private:
    int numTubes;
    Tube* tubes;
};

#endif // GAME_H
