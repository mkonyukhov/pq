#include <vector>
#include <iostream>
#include "pq.hpp"

using namespace std;

int main()
{
	try {
		priority_queue<double, greater<double> > dg;
		vector<double> vd(44, 3.14);
		dg.push(vd, 4);
		priority_queue<double, greater<double> >::reverse_iterator CRI = dg.rbegin();
		while(CRI != dg.rend())
		{
			cout << *CRI << ' ';
			++CRI;
		}
		cout << '\n';
		priority_queue<int, greater<int> > ig;
		vector<int> vi;
		for(unsigned int i = 0; i < 21; i++) vi.push_back(i);
		ig.push(vi);
		for(int i = 0; i < 10; ++i)  {
			cout << ig.top() << ' ';
			ig.pop();
		}
		cout<<'\n';
		ig.print();
		cout << dg.size() << ' ' << dg.capacity() << ' ' << ig.empty() << endl;
		priority_queue<int, greater<int> > ig_ = ig;
		if(ig == ig_) cout << "ig==ig_\n";
		int elem;
		ig.pop(elem);
		cout << elem << endl;
		if(ig != ig_) cout << "ig!=ig_\n";
		ig.print();
		if(ig < ig_) cout << "ig<ig_\n";
		if(ig_ > ig) cout << "ig_>ig\n";
	}
	catch(UnderflowException) 
		{ cout << "Error: priority queue is empty\n"; }
		
    return 0;
}
