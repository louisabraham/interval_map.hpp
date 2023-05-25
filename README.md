# Interval map

Implementation of a map data structure that allows to store and retrieve values by intervals. The code uses templates to allow any type of key and value.

Instad of using an interval tree, this implementation uses a std::map to store boundary keys.

Finally, the class takes a default value that is returned when no interval is found.

## Usage

```cpp
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
```

## Tests

```bash
g++ --std=c++17 tests.cpp -fsanitize=address -o tests && ./tests
```