#include "tube.h"
#include <iostream>

using namespace std;

Tube::Tube() : size_(0) {}

Tube::Tube(stack<pair<string, int>> colors) : colors(colors) {
    size_ = 0;
    while (colors.size() != 0) {
        size_ += colors.top().second;
        colors.pop();
    }
}

int Tube::add(pair<string, int> toAdd) {
    string color = toAdd.first;
    int num = toAdd.second;

    int numToAdd = min(num, CAPACITY - size_);

    if (size_ == 0) {
        colors.push({color, numToAdd});
        size_ += numToAdd;
        return numToAdd;
    }

    if (size_ >= CAPACITY || colors.top().first != color) {
        return 0;
    }

    int numAlreadyIn = colors.top().second;
    colors.pop();
    colors.push({color, numAlreadyIn + numToAdd});

    size_ += numToAdd;
    return numToAdd;
}

pair<string, int> Tube::remove() {
    if (size_ == 0) {
        return {};
    }

    pair<string, int> toRemove = colors.top();
    colors.pop();
    size_ -= toRemove.second;
    return toRemove;
}

pair<string, int> Tube::remove(int num) {
    if (size_ == 0 || num == 0) {
        return {};
    }

    pair<string, int> toRemove = colors.top();
    int numToRemove = min(num, toRemove.second);
    colors.pop();

    int numLeft = toRemove.second - numToRemove;
    if (numLeft > 0) {
        colors.push({toRemove.first, numLeft});
    }

    size_ -= numToRemove;
    return {toRemove.first, numToRemove};
}

pair<string, int> Tube::peek() {
    if (size_ != 0) {
        return colors.top();
    }
    return {};
}

int Tube::size() {
    return size_;
}

void Tube::print() {
    stack<pair<string, int>> s = colors;
    while (!s.empty()) {
        pair<string, int> next = s.top();
        for (int i = 0; i < next.second; i++) {
            cout << next.first << endl;
        }
        s.pop();
    }
}
