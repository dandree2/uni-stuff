
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

#include <iostream>
#include <memory> //For the usage of shared pointers.
#include <vector> //For the usage of vector - dynamic array representation.
#include <algorithm>

#include"Car.h"

/* Template is used for generalizing the PrintData function.
   It could be used for both Vehicle and Car, but only after some clever changes!
   */
template <typename T>
void PrintData(const T& input_param);

/* Why it is not called InitData? 
   Do we have to check for null? */
void InitCar(Car& p_car, uint16_t p_year, float p_engineVol);

/* Base class*/
int main()
{
	/* Car created on the Stack and it's initialized. How? */
	Car car;

	/* Car created through its Base class on the Heap. Is it initialized? */
	Vehicle *dyn_vehicle = new Car();

	/* Smart unique pointer, which should point a Car object. Does it do it now? */
	std::unique_ptr<Car> first_car_ptr; //Try to print it!

	/* Smart unique pointer, which should point a Car object. */
	std::unique_ptr<Car> second_car_ptr(new Car());
	InitCar(*second_car_ptr, 1994, 2.4f); //Initialize with some different values.

	/* We are creating a dynamic array/vector of cars. */
	std::vector<Car> vector_of_cars; //Is it created now? Can we print it?

	vector_of_cars.emplace_back(car); //We add a new element. Take a look at the Terminal!
	vector_of_cars.push_back(*second_car_ptr); //We add another new element. We use another function for it - why? Take a look at the Terminal again!

	/* BRACE YOURSELVES! WE'RE TRANSFORMING A VEHICLE TO A CAR!!! */
	/* * is because we need a value behind a pointer;
	   dynamic_cast will do the trick;
	   Car * is the pointer to the type of the wanted object/class
	   dyn_vehicle is the is a pointer to Vehicle, instantiated as a Car earlier.
	*/
	vector_of_cars.push_back(*(dynamic_cast<Car*>(dyn_vehicle))); //Be cautios when you do this. It's dirty!

	/* PRINTING ELEMENTS OF A VECTOR */

	/* Let's see what we have in the vector.
	   Remember the auto variables?
	   */
	for (const auto& car : vector_of_cars) {
		PrintData<Car>(car);
	}

	/* Printing the elements, using an iterator.
	   Why not const auto? Why not a reference.
	   Why ++it, instead of it++
	*/
	for (auto it = vector_of_cars.begin(); it != vector_of_cars.end(); ++it) {
		PrintData<Car>(*it); //Why do we need *
	}

	/* Printing the cars related to a certain criterion. */
	/* This is a bad example for usage of the lambda - it's too long for a one-liner. */
	/* Usage of static_cast is also only for demonstration purposes. */
	/* Please take a look at the enum class more carefully. */
	std::for_each(vector_of_cars.begin(), vector_of_cars.end(),
		[](const auto& p_car) { if (static_cast<Car::Classification>(p_car.GetYear()) < Car::Classification::old_car) 
			PrintData<Car>(p_car); });

	/* Creating a lambda variable, using auto. */
	/* This will return "true" if the car is older than "old_car" and "false" if not! */
	auto lambda = [](const auto& p_car)->bool {
		if (static_cast<Car::Classification>(p_car.GetYear()) < Car::Classification::old_car)
			return true;
		else return false;
	};

	/* REMOVING ELEMENTS FROM A VECTOR, BASED ON SOME CRITERIA. */

	/* The lambda will mark if the car is older then some year. */
	/* The remove_if will move all elements, where lambda will return "true" to the end of the vector. */
	/* remove_if will return an iterator to the first element that's to-be-deleted. */
	/* erase will receive the remove_if iterator and the iterator, marking the end of the vector. */
	/* It will delete all elements between them. */
	/* Try "=delete" the move assignment operator of the car - see what happens. Why? */
	vector_of_cars.erase(std::remove_if(vector_of_cars.begin(), vector_of_cars.end(), lambda ), vector_of_cars.end());

	std::cout << "----------------" << std::endl;

	/* Print the array after removal. */
	for (const auto& car : vector_of_cars) {
		PrintData<Car>(car);
	}

	delete dyn_vehicle; //Take a look at the Destructor's call in the Terminal!

	return 0;
}

template <typename T>
void PrintData(const T& input_param) {
	std::cout << input_param.GetYear() << " " << input_param.GetEngineVolume() << std::endl;
}

void InitCar(Car& p_car, uint16_t p_year, float p_engineVol) {
	p_car.SetYear(p_year);
	p_car.SetEngineVolume(p_engineVol);
}
