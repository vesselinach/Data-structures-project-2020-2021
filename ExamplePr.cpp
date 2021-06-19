


#include "Parser.h"
#include <fstream>

int main()
{
	Json json;
	json.read("input2.txt");
	json.print();
	std::cout << "\n \n";
	std::vector<Token*> tokens;
	json.makeTokens(tokens);
	//Parser p;
	//for (Token* t : tokens)
	//{
		//t->print(std::cout);
		//std::cout << '\n';
	//}
	//p.parse(tokens);



	//?????????????????????????
	/*
	void createTextFile(const HashTable<StringToken, Token*> table)
	{
		std::ofstream fileOut("File.txt");
		if (fileOut.is_open())
		{
			fileOut << table;

		}
		else
		{
			std::cout << "Unable to open\n";
		}

		fileOut.close();
	} */

	
}

