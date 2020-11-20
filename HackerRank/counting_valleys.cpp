#include<iostream>

int countingValleys(int steps, std::string path) {
	int level = 0;
	int valleys = 0;

	for (const auto idx : path) {
		if (idx == 'D') --level;
		if (idx == 'U') ++level;

		if (level == 0 and idx == 'U') ++valleys;
	}

	return valleys;
}


int main()
{
	std::string input = "DDUUDDUDUUUD";
	std::cout<<countingValleys(input.length(), input);

	return 0;
}