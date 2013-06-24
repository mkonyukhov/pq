#include <vector>
#include <iostream>
#include "pq.hpp"

int main()
{
	try {

		std::vector<double> vd(44, 3.14);
		
		priority_queue<double, std::greater<double>> dg(vd, 2);
		
		for (auto i : dg) {
		    std::cout << i << std::endl; 
		}
	}
	
	catch(UnderflowException) {
	    std::cout << "Error: priority queue is empty\n";
	}
		
    return 0;
}
