#include <iostream>

class car {
	public:
	virtual void move() {
		std::cout << "car move" << std::endl;
 	}
};

class electric_car : public car {
	public:
	void move() {
		std::cout << "electric_car move" << std::endl;
 	}
};
struct my_string : public std::string {
	my_string(char chart[]) : std::string (chart == 0 ? "" : chart) {}
};

void f(car& c) {
	c.move();
}

void f2(car c) {
	c.move();
}
int main() {
	car * ec = new electric_car();
	ec->move();
	
	f(*ec);
	f2(*ec);
	
	car* ec2 = new electric_car(*ec);
	
	my_string s(0);
	std::cout << s << std::endl;
	
	/*if(s.size() == 0) {
		std::cout << "null string" << std::endl;
	}*/
	
	//s[0] = 'a';
}