#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
#include "interval_map.hpp"

bool VERBOSE = false;

void RandomTest()
{
    int QUERIES = 10;
    int MAX_RANGE = 21;

    auto chars = {'A', 'B', 'C', 'D', 'E'};
    auto random_char = [&chars]()
    {
        return *(chars.begin() + (rand() % chars.size()));
    };
    auto random_int = [](int n)
    {
        return rand() % n;
    };

    auto default_value = 'A';
    interval_map<int, char> interval(default_value);

    std::vector<std::pair<std::pair<int, int>, char>> queries;

    int query_number = random_int(QUERIES);
    std::cerr << "Testcase" << std::endl;
    for (int i = 0; i < query_number; ++i)
    {
        int start = random_int(MAX_RANGE);
        int end = random_int(MAX_RANGE);
        char val = random_char();
        std::cerr << "assign: " << start << " " << end << " " << val << std::endl;
        interval.assign(start, end, val);
        queries.push_back({{start, end}, val});
        interval.debug();
        std::cerr << "-----" << std::endl;
    }
    reverse(queries.begin(), queries.end());
    for (int p = -1; p < MAX_RANGE + 1; ++p)
    {
        auto ans = default_value;
        for (auto &q : queries)
        {

            if (q.first.first <= p && p < q.first.second)
            {
                ans = q.second;
                break;
            }
        }
        std::cerr << "query: " << p << " " << ans << " " << interval[p] << std::endl;
        assert(interval[p] == ans);
    }
    if (!interval.getMap().empty())
    {
        assert(interval.getMap().begin()->second != default_value);
        // assert that there are no two consecutive values in the map
        for (auto it = interval.getMap().begin(); it != prev(interval.getMap().end()); ++it)
        {
            assert(it->second != next(it)->second);
        }
        assert(interval.getMap().rbegin()->second == default_value);
    }
    std::cerr << "Testcase passed." << std::endl
              << std::endl;
}
void IntervalMapTest()
{
    // Test case 1: Initial interval map with 'A'
    interval_map<int, char> interval('A');
    interval.debug();
    assert(interval[0] == 'A');
    assert(interval[5] == 'A');
    assert(interval[-5] == 'A');

    interval.assign(1, 3, 'A');
    interval.debug();
    assert(interval[0] == 'A');
    assert(interval[5] == 'A');
    assert(interval[-5] == 'A');
    assert((interval.getMap() == std::map<int, char>{}));

    std::cerr << "Test case 1 passed." << std::endl
              << std::endl;

    // Test case 2: Assign 'B' to the interval [1, 3)
    interval.assign(1, 3, 'B');
    interval.debug();
    assert(interval[0] == 'A');
    assert(interval[1] == 'B');
    assert(interval[2] == 'B');
    assert(interval[3] == 'A');
    assert((interval.getMap() == std::map<int, char>{{1, 'B'}, {3, 'A'}}));

    std::cerr << "Test case 2 passed." << std::endl
              << std::endl;

    // Test case 3: Assign 'C' to the interval [2, 4)
    interval.assign(2, 4, 'C');
    interval.debug();
    assert(interval[1] == 'B');
    assert(interval[2] == 'C');
    assert(interval[3] == 'C');
    assert(interval[4] == 'A');
    assert((interval.getMap() == std::map<int, char>{{1, 'B'}, {2, 'C'}, {4, 'A'}}));

    std::cerr << "Test case 3 passed." << std::endl
              << std::endl;

    // Test case 4: Assign 'B' to the interval [5, 8)
    interval.assign(5, 8, 'B');
    interval.debug();
    assert(interval[4] == 'A');
    assert(interval[5] == 'B');
    assert(interval[7] == 'B');
    assert(interval[8] == 'A');
    assert((interval.getMap() == std::map<int, char>{{1, 'B'}, {2, 'C'}, {4, 'A'}, {5, 'B'}, {8, 'A'}}));

    std::cerr << "Test case 4 passed." << std::endl
              << std::endl;

    // Test case 5: Assign 'A' to the interval [1, 2)
    interval.assign(1, 2, 'A');
    interval.debug();
    assert(interval[0] == 'A');
    assert(interval[1] == 'A');
    assert(interval[2] == 'C');
    assert((interval.getMap() == std::map<int, char>{{2, 'C'}, {4, 'A'}, {5, 'B'}, {8, 'A'}}));

    std::cerr << "Test case 5 passed." << std::endl
              << std::endl;

    // Test case 6: Assign 'A' to the interval [3, 6)
    interval.assign(3, 6, 'A');
    interval.debug();
    assert(interval[2] == 'C');
    assert(interval[3] == 'A');
    assert(interval[5] == 'A');
    assert(interval[7] == 'B');
    assert((interval.getMap() == std::map<int, char>{{2, 'C'}, {3, 'A'}, {6, 'B'}, {8, 'A'}}));

    std::cerr << "Test case 6 passed." << std::endl
              << std::endl;

    // Test case 7: Assign 'D' to the interval [-2, 1)
    interval.assign(-2, 1, 'D');
    interval.debug();
    assert(interval[-3] == 'A');
    assert(interval[-2] == 'D');
    assert(interval[0] == 'D');
    assert(interval[1] == 'A');
    assert((interval.getMap() == std::map<int, char>{{-2, 'D'}, {1, 'A'}, {2, 'C'}, {3, 'A'}, {6, 'B'}, {8, 'A'}}));

    std::cerr << "Test case 7 passed." << std::endl
              << std::endl;

    // Test case 8: Empty interval assignment
    interval.assign(3, 3, 'D');
    interval.debug();
    assert(interval[2] == 'C');
    assert(interval[3] == 'A');
    assert(interval[4] == 'A');
    assert((interval.getMap() == std::map<int, char>{{-2, 'D'}, {1, 'A'}, {2, 'C'}, {3, 'A'}, {6, 'B'}, {8, 'A'}}));

    std::cerr << "Test case 8 passed." << std::endl
              << std::endl;

    // Test case 9: Assign 'A' to the interval [4, 5)
    interval.assign(4, 5, 'A');
    interval.debug();
    assert((interval.getMap() == std::map<int, char>{{-2, 'D'}, {1, 'A'}, {2, 'C'}, {3, 'A'}, {6, 'B'}, {8, 'A'}}));

    std::cerr << "Test case 9 passed." << std::endl
              << std::endl;

    // Test case 10: Assign 'A' to the interval [8, 10)
    interval.assign(8, 10, 'A');
    interval.assign(8, 9, 'A');
    interval.debug();
    assert((interval.getMap() == std::map<int, char>{{-2, 'D'}, {1, 'A'}, {2, 'C'}, {3, 'A'}, {6, 'B'}, {8, 'A'}}));

    std::cerr << "Test case 10 passed." << std::endl
              << std::endl;

    // Test case 11: Assign 'A' to the interval [7, 10)
    interval.assign(7, 10, 'A');
    interval.debug();
    assert((interval.getMap() == std::map<int, char>{{-2, 'D'}, {1, 'A'}, {2, 'C'}, {3, 'A'}, {6, 'B'}, {7, 'A'}}));

    std::cerr << "Test case 11 passed." << std::endl
              << std::endl;

    // Test case 12: Assign 'B' to the interval [7, 10)
    interval.assign(7, 10, 'B');
    interval.debug();
    assert((interval.getMap() == std::map<int, char>{{-2, 'D'}, {1, 'A'}, {2, 'C'}, {3, 'A'}, {6, 'B'}, {10, 'A'}}));

    std::cerr << "Test case 12 passed." << std::endl
              << std::endl;

    // Test case 13: Assign 'B' to the interval [5, 9)
    interval.assign(5, 9, 'B');
    interval.debug();
    assert((interval.getMap() == std::map<int, char>{{-2, 'D'}, {1, 'A'}, {2, 'C'}, {3, 'A'}, {5, 'B'}, {10, 'A'}}));

    std::cerr << "Test case 13 passed." << std::endl
              << std::endl;

    // Test case 14: Assign 'A' to the interval [11, 12)
    interval.assign(11, 12, 'A');
    interval.debug();
    assert((interval.getMap() == std::map<int, char>{{-2, 'D'}, {1, 'A'}, {2, 'C'}, {3, 'A'}, {5, 'B'}, {10, 'A'}}));

    std::cout << "All small test cases passed." << std::endl;
}

int main()
{
    if (!VERBOSE)
        // disable cerr
        std::cerr.setstate(std::ios_base::failbit);
    IntervalMapTest();
    srand(time(NULL));
    int N_TESTS = 10000;
    for (int i = 0; i < N_TESTS; ++i)
        RandomTest();
    std::cout << "All random test cases passed." << std::endl;

    return 0;
}
