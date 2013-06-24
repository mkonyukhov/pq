#include <cstring>
#include <iostream>
#include "pq.hpp"
#include <queue>

int main (int argc, char const *argv[])
{
    priority_queue<int, std::greater<int>> a;
    
    a.push(2);
    a.push(3);
    
    std::priority_queue<int, std::vector<int>, std::greater<int>> b;
    
    b.push(2);
    b.push(4);

  return 0;
}
