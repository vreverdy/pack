#include <vector>
#include <deque>
#include <list>
#include <iostream>
#include "../include/pack.hpp"

using namespace pck;

template <class...>
void print()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main(int argc, char* argv[])
{
    auto x = pack<std::vector, std::list, std::deque>();
    auto y = pack<1, 2, 3, 4>();
    print<decltype(x)>();
    print<decltype(y)>();
    return 0;
}
