#include <vector>
#include <iostream>
#include "pq.hpp"

int main()
{
	try {

		std::vector<double> vd(44, 3.14);
		
		priority_queue<double, std::greater<double>> qd(vd, 2);
		
		for (auto i : qd) {
		    std::cout << i << std::endl; 
		}
	} catch(UnderflowException) {
	    std::cout << "Error: priority queue is empty\n";
	}
		
    return 0;
}
