#include<iostream>

class Base {
public:
	Base() {
		std::cout << "Base constructed\n";
	}
	virtual ~Base() {
		std::cout << "Base destructed\n";
	}
};

class A :  virtual Base {
public:
	A() {
		std::cout << "A constructed\n";
	}

	virtual ~A() {
		std::cout << " A destructed\n";
	}
};

class B :  virtual Base {
public:
	B() {
		std::cout << "B constructed\n";
	}

	virtual ~B() {
		std::cout << "B destructed\n";
	}
};

class a : virtual A, B {
public:
	a() {
		std::cout << "a constructed\n";
	}

	virtual ~a() {
		std::cout << "a destructed\n";
	}
};

int main() {

	a test; //What happens if we play around with the term "virtual?"
	return 0;
}