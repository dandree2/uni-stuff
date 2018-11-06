// DISCLAIMER: These files are only for studying and teaching purposes!
// They are not intendet to be a direct example of good coding practices 
// or C++ expert usage.
//

/*
	Copyright 2018 Desislav Andreev: desislav.andreev@gmail.com

	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute,
	sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
	DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include<iostream>

#include"Car.h"

/*
// Deleted in the class definition, because it shouldn't be used at this point.
Car::Car(){
	std::cout << "Car's default constructor is called!" << std::endl;
}
*/

/* Car's constructor with initializer list. 
   We make sure the variable/object is completelly constructed
   and initialized, before we really start using it.
   Reference and constant members are initialized here, too.
   */
Car::Car() : m_year(2018), m_engineVolume(3.5f){
	std::cout << "Car constructed with initializer list!" << std::endl;
}

/* Car's Copy constructor implementation. */
Car::Car(const Car& car) {
	std::cout << "Car's copy constructor is called!" << std::endl;

	/* We are doing this for practice.
	   Local (inner) usage of these objects allows public member-variables. 
	   Usage of accessor and mutators will be obsolete. */
	  m_year = car.m_year;
      m_engineVolume = car.m_engineVolume;
}

/* Car's implementation of the Assignment operator. */
Car& Car::operator=(const Car& other_car) {
	std::cout << "Car's assignment operator is called!" << std::endl;

	/* Could left and right operands be the same reference?
	   Must we check if they are the same before we do the assignment?
	   If yes - what would we have to implement additionally?
	   */
	 m_year = other_car.m_year;
	 m_engineVolume = other_car.m_engineVolume;

	return *this;
}

/* Car's implementation of the Move assignment operator. */
Car& Car::operator=(Car && other_car) {

	std::cout << "Car's move assignment operator is called!" << std::endl;
	if (this != &other_car)
	{
		this->m_engineVolume = other_car.GetEngineVolume();
		this->m_year = other_car.GetYear();

		/* Do we need to do that? */
		other_car.SetEngineVolume(0.0f);
		other_car.SetYear(0);
	}

	return *this;
}

/* Car's destructor implementation. */
Car::~Car() {
	std::cout << "Car's destructor called!" << std::endl;
}

uint16_t Car::GetYear() const {
	return m_year;
}

float Car::GetEngineVolume() const {
	return m_engineVolume;
}

void Car::SetYear(uint16_t p_year) {
	m_year = p_year;
}

void Car::SetEngineVolume(float p_engineVol) {
	m_engineVolume = p_engineVol;
}