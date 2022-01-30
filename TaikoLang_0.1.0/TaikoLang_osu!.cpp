#include <iostream>
#include <fstream>
#include <vector>

#define SIZE_PTR	(1 << 15)
#define SIZE_CELL	(1 << 8)

std::string file_path, bfcode;
std::vector<unsigned char> array(SIZE_PTR, 0);
int ptr = 0, bracket_nest = 0;

void get_file_path()
{
	std::cout << "[TaikoLang Interpreter - osu! v0.1.0]" << "\n\n";
	std::cout << "<Enter Your TaikoLang File (.osu) Path Here>" << "\n";
	std::cout << "--------------------------------" << "\n";
	
	std::getline(std::cin, file_path);
	std::cout << "--------------------------------" << "\n\n";
}

void convert_code() /* Converts .osu file to Brainfuck */
{
	std::ifstream osu_file(file_path);
	std::string line, dummy_value, object_type, hitsound;
	char separator, newline;
	
	if (osu_file.is_open())
	{
		while (!osu_file.eof())
		{
			std::getline(osu_file, line);
			if (line == "[HitObjects]")
				break;
				
		}
		
		int token = 0, cur = 2;
		
		while (!osu_file.eof()) /* Hit object syntax in .osu: "x,y,time,type,hitSound,objectParams,normalSet:additionSet:index:volume:filename:" */
		{
			for (int param = 1; param <= 3; param ++) /* We don't care about the first 3 parameters */
				std::getline(osu_file, dummy_value, ',');
			
			std::getline(osu_file, object_type, ',');
			
			if (stoi(object_type) & (1 << 1) || stoi(object_type) & (1 << 3)) /* Omits the entire line if the object is a slider (1) or spinner (3) */
				std::getline(osu_file, dummy_value);
			
			else
			{
				std::getline(osu_file, hitsound, ',');
				/* std::cout << stoi(hitsound) << " "; */ /* Test */
				
				if (stoi(hitsound) & (1 << 1) || stoi(hitsound) & (1 << 3)) /* Hitsound bit flags (1: whistle, 3: clap) to determine the color of notes */
				{
					token += (1 << cur);
					cur --;
				}
				
				else
					cur --;
				
				if (cur < 0)
				{
					bfcode.push_back("><+-.,[]"[token]);
					cur = 2;
					token = 0;
				}
				
				std::getline(osu_file, dummy_value); /* We also don't care about the rest of the parameters */
			}
		}
	}
	
	osu_file.close();
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
	get_file_path();
	convert_code();
	interpret_bfcode();
	
	return 0;
}
