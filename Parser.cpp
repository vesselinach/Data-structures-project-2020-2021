#include "Parser.h"
#include "Json.h"

void Parser::printTable()
{
	this->table.printHashTable();
}

void Parser::parse(const std::vector<Token*>& tokens)
{
	
	unsigned size = tokens.size();
	
	if (tokens[0]->type != Type::OpennningBracket)
	{
		std::cout << "Expected oppenning bracket";
		return;
	}
	for (size_t i = 1; i <size; i+= 4)
	{
		if (tokens[i+1]->type != Type::Dots)
		{
			std::cout << "Expected dots ";
			return;
		}
		table.addNewValue(*(dynamic_cast<StringToken*>(tokens[i])),tokens[i+2]);
		if (tokens[i+3]->type != Type::Comma)
		{
			if (tokens[i+3]->type != Type::ClosingBracket)
			{
				std::cout << "Expected comma or clossing bracket";
				return;
			}
			table.printHashTable();
			std::cout << "Successsfully parsed!";
			return;
		}
	}
	
	
}
void Parser::findByKey(StringToken* key)
{
	Token* result = this->table.getValue(*key);
	table.isValid(*key, result);
	if (table.isValid(*key, result) == true)
	{
		result->print(std::cout);
		return;
	}
	std::cout << "Invalid key!";

}
void Parser::removeElement(StringToken* key)
{
	Token* result = this->table.getValue(*key);
	table.isValid(*key, result);
	if (table.isValid(*key, result) == true)
	{
		this->table.removeValue(*key);
		return;
	}
	std::cout << "Invalid key!";
	
}

void Parser::sortByKey(const StringToken* key)
{
	Token* result = this->table.getValue(*key);
	table.isValid(*key, result);
	if (table.isValid(*key, result) == false)
	{
		std::cout << "Invalid key!";
		return;
	}
	if (result->type != Type::Array)
	{
		std::cout << "Expected an array!";
		return;
	}
	ArrayToken* value = dynamic_cast<ArrayToken*>(result);
	if (value->arrayData[0]->type == Type::Number)
	{
		unsigned arraySize = value->arrayData.size();
		std::vector<double> nums;
		for (size_t i = 0; i < arraySize; i++)
		{
			nums.push_back(dynamic_cast<NumberToken*>(value->arrayData[i])->num);
		}
		sortNumbers(nums, arraySize);
		std::vector<Token*> sorted;
		for (size_t i = 0; i < arraySize; i++)
		{
			sorted.push_back(new NumberToken(nums[i]));
		}
		table.addNewValue(*key, new ArrayToken(sorted));
		return;
	}
	if (value->arrayData[0]->type == Type::String)
	{
		unsigned arraySize = value->arrayData.size();
		std::vector<std::string> strings;
		for (size_t i = 0; i < arraySize; i++)
		{
			strings.push_back(dynamic_cast<StringToken*>(value->arrayData[i])->data);
		}
		sortStrings(strings, arraySize);
		std::vector<Token*> sorted;
		for (size_t i = 0; i < arraySize; i++)
		{
			sorted.push_back(new StringToken(strings[i]));
		}
		table.addNewValue(*key, new ArrayToken(sorted));
		return;
	}
	std::cout << "Invalid value type. Expected a number or string";
}

void Parser::addNewElementInTable(const StringToken& mykey, Token* newElement)
{
	size_t size = this->table.getSize();
	if (!(newElement->type == Type::Array || newElement->type == Type::Boolean || newElement->type == Type::Number ||
		newElement->type == Type::String || newElement->type == Type::Null))
	{
		std::cout << "Incorrect validated!";
		return;
	}
	while (size != 0)
	{
		if (table.isValid(mykey, newElement) == true) 
		{
			std::cout << "This element has already existed in the table! ";
			return;
		}
		else 
		{
			table.addNewValue(mykey, newElement);
		}
	}
	
}

void Parser::reverseElements(const StringToken& key1, const StringToken& key2)
{
	Token* element = table.getValue(key1);
	Token* element2 = table.getValue(key2);

		if (table.isValid(key1, table.getValue(key1)) == true)
		{
			table.removeValue(key1);
		}
		if (table.isValid(key2, table.getValue(key2)) == true)
		{
			table.removeValue(key2);
		}
	
		table.addNewValue(key1, element2);
		table.addNewValue(key2, element);

}
void Parser:: changeElement(const StringToken& mykey, Token* changingElement)
{
	Token* elementTemp = table.getValue(mykey);

	if (!(changingElement->type == Type::Array || changingElement->type == Type::Boolean || changingElement->type == Type::Number ||
		changingElement->type == Type::String || changingElement->type == Type::Null)){
		std::cout << "Incorrect validated!";
		return;
	}
	if (table.isValid(mykey, changingElement) == true)
	{
		std::cout << "This element could not be replaced!";
		return;
	}
	table.removeValue(*(dynamic_cast<StringToken*>(elementTemp)));
	table.addNewValue(mykey, changingElement);


}
void Parser::writeInFile(const StringToken* mykey) 
{
	
	
	std::ofstream fileName("input3.txt");

	if (fileName.is_open())
	{

		Token* result = this->table.getValue(*mykey);
		size_t size = this->table.getSize();
		if (table.isValid(*mykey, result) == false)
		{
			std::cout << "Invalid key!";
			return;
		}

		NumberToken* valueNum = dynamic_cast<NumberToken*>(result);
		if (result->type == Type::Number)
		{
			double numberPerFile = valueNum->num;
			fileName << numberPerFile;
		}
		BooleanToken* valueBool = dynamic_cast<BooleanToken*>(result);
		if (result->type == Type::Boolean)
		{
			bool boolPerFile = valueBool->data;
			fileName << boolPerFile;
		}
		StringToken* valueString = dynamic_cast<StringToken*>(result);
		if (result->type == Type::String)
		{
			std::string stringPerFile = valueString->data;
			fileName << stringPerFile;
		}
		ArrayToken* arrayT = dynamic_cast<ArrayToken*>(result);
		std::vector<Token*> valueArr = arrayT->arrayData;
		//unsigned arraySize = valueArr->arrayData.size();
		for (std::vector<Token*> ::iterator it = valueArr.begin(); it != valueArr.end(); ++it)
		{
			if (dynamic_cast<StringToken*>(*it))
			{
				fileName << dynamic_cast<StringToken*>(*it)->data;
			}
			else if (dynamic_cast<NumberToken*>(*it))
			{
				fileName << dynamic_cast<NumberToken*>(*it)->num;
			}
			else if (dynamic_cast<BooleanToken*>(*it))
			{
				fileName << dynamic_cast<BooleanToken*>(*it)->data;
			}

		}
	}
	else
	{
		std::cout << "Unable to open file.\n";
		return;
	}
	fileName.close();
				
	

}
void Parser::createTextFile(const std::string& fileName)
{
	
	size_t size = table.getSize();
	std::ofstream outFile;
	outFile.open(fileName);
	
	size_t size = table.getSize();
	if (outFile.is_open())
	{
		
		table.printHashTableToFile(outFile);
	}
	else
	{
		std::cout << "Unable to open file.\n";
		return;
	}
	outFile.close();
	

}
	




void Parser::sortNumbers(std::vector<double>& numbers, unsigned size)
{
	
	for (size_t i = 0; i < size -1 ; i++)
	{
		unsigned currMinIdx = i;
		for (size_t j = i+1; j < size; j++)
		{
			if (numbers[j] < numbers[currMinIdx])
			{
				currMinIdx = j;
			}
		}
		double temp = numbers[i];
		numbers[i] = numbers[currMinIdx];
		numbers[currMinIdx] = temp;
	}
}

void Parser::sortStrings(std::vector<std::string>& strings, unsigned size)
{
	for (size_t i = 0; i < size - 1; i++)
	{
		unsigned currMinIdx = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (strings[j] < strings[currMinIdx])
			{
				currMinIdx = j;
			}
		}
		std::string temp = strings[i];
		strings[i] = strings[currMinIdx];
		strings[currMinIdx] = temp;
	}
}


Token Parser::searchByIndex(unsigned index)
{
	std::vector<Token*> myData;
	table.toArray(myData);
	size_t resultSize = myData.size();
	Token* result = new Token[resultSize];
	for (size_t i = 0; i < resultSize; i++)
	{
		result[i] = *myData[i];
	}
	return result[index];

}

Parser::Parser()
{
	table = {};
}



/*
	std::string** array = new std::string * [size];
	for (int i = 0; i < size; ++i)
		array[i] = new std::string[size];

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			array[i][j];
		}
	}


	std::cout << array[size][size] << std::endl;


	for (int i = 0; i < size; ++i)
		delete[] array[i];

	delete[] array;
	/*
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j <size; j++)
		{
			std::string array = value[i][j];
			std::cout << array << endl;
		}
	}*/

