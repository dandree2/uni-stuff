#include"Vehicle.h"
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

/* Definition of class Car */
class Car : public Vehicle {
public:
	/* List of constructors */
	Car(); //Remember why we use "delete"!
	Car(const Car&);
	Car(Car&&) = delete; //test

	/* Operator overloads */
	Car& operator=(const Car&);
	Car& operator=(Car &&);

	/* Accessors and mutators - should they be here or in the Base class? */
	/* Do we want to generalize their usage? */
	uint16_t GetYear() const;
	float GetEngineVolume() const;
	
	void SetYear(uint16_t);
	void SetEngineVolume(float);

	/* Destructor */
	~Car();

	/* Example for an enum class. */
	enum class Classification : uint16_t {
		old_car = 2005,
		brand_new = 2018
	};

private:
	uint16_t m_year;
	float m_engineVolume;
};

