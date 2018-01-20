#include <iostream>

#include "BogdanovArray.h"

int main()
{
	BogdanovArray <int> myArray = { 1, 2, 3, 5 };
	BogdanovArray <int> movement = { 666 };
	movement = std::move(myArray);
	movement.resize(2);
	for (size_t i = 0; i < movement.getSize(); ++i)
		std::cout << movement[i];
}
