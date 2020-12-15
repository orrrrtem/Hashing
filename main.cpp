#include <iostream>
#include "ChainHash.hpp"


int main() {

    hash_table table(100);
    for(int i = 100; i < 100000; i+=100) {
        table.insert(i, i + 20);
    }
    table.insert(120, 21);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}