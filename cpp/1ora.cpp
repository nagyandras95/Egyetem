#include <iostream> // miért kell az include?
#include "csere.hpp"
#include <vector>
#include <list> 
#include <algorithm>    // std::reverse
#include <memory>

using namespace std; // mi az az std?

class A {
	public:
	A() {}
	A(const A& a) {
		counter++;
	}
	
	static int counter;
};

int A::counter = 0;

int main()
{
	
	std::vector<A> v;
	for(int i = 0; i < 10; ++i) {
		v.push_back(A());
	}
	std::cout << A::counter << std::endl;
	
	A::counter = 0;
	std::list<A> l;
	for(int i = 0; i < 10; ++i) {
		l.push_back(A());
	}
	
	std::cout << A::counter << std::endl;
	
	A::counter = 0;	
	std::reverse(v.begin(),v.end()); 
	std::cout << A::counter << std::endl;

	A::counter = 0;	
	l.reverse(); 
	std::cout << A::counter << std::endl;
	
	std::unique_ptr<A> ptr_A = std::unique_ptr<A>(new A());

	return 0;
}






