#include <iostream>
#include <vector>

#define SIZE_PTR	(1 << 15)
#define SIZE_CELL	(1 << 8)

std::string input, bfcode;
std::vector<unsigned char> array(SIZE_PTR, 0);
int ptr = 0, bracket_nest = 0;

void get_input()
{
	std::cout << "[TaikoLang Interpreter - text v0.1.0]" << "\n\n";
	std::cout << "<Enter Your Code Here>" << "\n";
	std::cout << "--------------------------------" << "\n";
	
	getline(std::cin, input);
	std::cout << "--------------------------------" << "\n\n";
}

void convert_code() /* Converts taiko notation to Brainfuck */
{
	int token = 0, cur = 2;
	
	for (int idx = 0; idx < input.size(); idx ++)
	{
		if (input[idx] == 'd' || input[idx] == 'D')
			cur --;
		
		else if (input[idx] == 'k' || input[idx] == 'K')
		{
			token += (1 << cur);
			cur --;
		}
		
		if (cur < 0)
		{
			bfcode.push_back("><+-.,[]"[token]);
			cur = 2;
			token = 0;
		}
	}
}

void interpret_bfcode() /* A simple Brainfuck interpreter */
{
	std::cout << "<Execution>" << "\n";
	std::cout << "--------------------------------" << "\n";
	
	int idx = 0;
	while (idx < bfcode.size())
	{
		switch (bfcode[idx])
		{
			case '>':
				ptr = (ptr + 1) % SIZE_PTR;
				break;
			
			case '<':
				ptr = (ptr - 1 + SIZE_PTR) % SIZE_PTR;
				break;
			
			case '+':
				array[ptr] = (array[ptr] + 1) % SIZE_CELL;
				break;
			
			case '-':
				array[ptr] = (unsigned char)(((int)array[ptr] - 1 + SIZE_CELL) % SIZE_CELL);
				break;
			
			case '.':
				std::cout << array[ptr];
				break;
			
			case ',':
				std::cin >> array[ptr];
				break;
			
			case '[':
				if (array[ptr] == 0)
				{
					bracket_nest ++;
					while (bfcode[idx] != ']' || bracket_nest != 0)
					{
						idx ++;
						if (bfcode[idx] == '[')
							bracket_nest ++;
						else if (bfcode[idx] == ']')
							bracket_nest --;
					}
				}
				break;
			
			case ']':
				if (array[ptr] != 0)
				{
					bracket_nest ++;
					while (bfcode[idx] != '[' || bracket_nest != 0)
					{
						idx --;
						if (bfcode[idx] == ']')
							bracket_nest ++;
						else if (bfcode[idx] == '[')
							bracket_nest --;
					}
				}
					
				break;
		}
		idx ++;
	}
}

int main()
{
	get_input();
	convert_code();
	interpret_bfcode();
	
	return 0;
}
