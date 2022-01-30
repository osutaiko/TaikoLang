#include <iostream>

std::string input;

int main()
{
	std::cout << "Enter your Brainfuck code here:" << "\n\n";
	
	getline(std::cin, input);
	std::cout << "\n";
	
	std::cout << "TaikoLang with spaces:" << "\n\n";
	
	for (int idx = 0; idx < input.size(); idx ++) /* There's probably a way to do this without using cases, but I'm too lazy */
		switch (input[idx])
		{
			case '>':
				std::cout << "ddd" << " ";
				break;
			
			case '<':
				std::cout << "ddk" << " ";
				break;
			
			case '+':
				std::cout << "dkd" << " ";
				break;
			
			case '-':
				std::cout << "dkk" << " ";
				break;
			
			case '.':
				std::cout << "kdd" << " ";
				break;
			
			case ',':
				std::cout << "kdk" << " ";
				break;
			
			case '[':
				std::cout << "kkd" << " ";
				break;
			
			case ']':
				std::cout << "kkk" << " ";
				break;
		}
	
	return 0;
}
