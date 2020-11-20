#include<iostream>

class Car {
public:
	Car();
	Car(uint16_t);
	virtual ~Car();
	Car(const Car&) = delete;
	Car(Car&&) noexcept;
	Car& operator= (const Car&); //Assingment overload
	Car& operator= (Car&&) noexcept;

	uint16_t m_year;
};

Car::Car() : m_year(1000) {
	std::cout << "Car constructed\n!";
}

Car::Car(uint16_t year) {
	std::cout << "Car constructed!";
	this->m_year = year;

	std::cout << " year: " << this->m_year << "\n";
}

Car::Car(Car&& other) noexcept : m_year(std::move(other.m_year)) {
	std::cout << "Move constructor: " << this->m_year << " to " << other.m_year << "\n";
	other.m_year = 0;
}

Car& Car::operator=(const Car& other) {
	std::cout << "Copy assignment: " << this->m_year << " to " << other.m_year << "\n";

	if (this != &other) {
		this->m_year = other.m_year;
	}

	return *this;
}

Car& Car::operator=(Car&& other) noexcept{
	std::cout << "Pointer moved from: " << this->m_year << " to " << other.m_year << "\n";

	if (this != &other) {
		this->m_year = other.m_year;
	}

	return *this;
}

Car::~Car() {
	std::cout << "Car destructed\n!";
}


int main() {
	Car c{ 1994 };
	Car b = std::move(c);
	//Play around with the other constructors.
	
	return 0;
}