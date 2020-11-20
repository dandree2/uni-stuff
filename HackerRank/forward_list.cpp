#include<iostream>
#include<algorithm>
#include<list>
#include<forward_list>
#include<string>
#include<vector>

void SplitString(std::string& to_split, std::forward_list<std::string>& output)
{
	const std::string delimiter = " ";
	std::string sub_string;
	size_t position = 0;

	for (; (position = to_split.find(delimiter)) != std::string::npos;)
	{
		sub_string = to_split.substr(0, position);
		output.push_front(sub_string); //Reverse list through creating it
		to_split.erase(0, position + delimiter.length());
	}
}

int main()
{
	std::string input = "This is string ";
	std::forward_list<std::string> output;
	SplitString(input, output);

	for (const auto& it : output)
	{
		std::cout << it << std::endl;
	}
	return 0;
}