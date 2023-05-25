#include <iostream>
#include <string>
#include "interval_map.hpp"

int main()
{
    interval_map<int, char> interval('A');
    interval.assign(0, 5, 'B');

    std::cout << interval[-1] << std::endl; // A
    std::cout << interval[0] << std::endl;  // B
    std::cout << interval[5] << std::endl;  // A
}