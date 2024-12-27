#ifndef TUBE_H
#define TUBE_H

#include <string>
#include <stack>

#define CAPACITY 4

class Tube {
public:
    Tube();

    Tube(std::stack<std::pair<std::string, int>> colors);
    
    // returns number of color added, 0 if fails
    int add(std::pair<std::string, int> toAdd);

    // returns removed color
    std::pair<std::string, int> remove();
    std::pair<std::string, int> remove(int num);

    std::pair<std::string, int> peek();

    int size();

    void print();
private:
    std::stack<std::pair<std::string, int>> colors;
    int size_;
};

#endif // TUBE_H
