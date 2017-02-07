#include <iostream>
#include "turmac/turmac.h"

int main() {
    turmac::example e = {};
    e.ex = "hello world";
    std::cout << e.ex << std::endl;
    turmac::printExample();
}