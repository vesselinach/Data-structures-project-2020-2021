#pragma once

#include<fstream>
#include<iostream>
#include <vector>
#include "HashMap.h"
#include "HashNode.h"
#include "Json.h"
#include <string>


class Parser
{
private:
	HashMap<StringToken, Token*> table;

	void sortNumbers(std::vector<double>& numbers, unsigned size);
	void sortStrings(std::vector<std::string>& strings, unsigned size);

	
public:

	Parser();
	


	void parse(const std::vector<Token*>& tokens);
	
	void printTable(); //a
	void findByKey(StringToken* key);//b
	void changeElement(const StringToken& key, Token* changingElement);//c
	void addNewElementInTable(const StringToken& mykey, Token* newElement); //d
	void removeElement(StringToken* key);//e
	void reverseElements(const StringToken& key1, const StringToken& key2);//f 
	void sortByKey(const StringToken* key); //g 

	Token searchByIndex(unsigned index);//h

	
	void writeInFile(const StringToken* mykey);//j
	void createTextFile(const std::string& stringInputToFile);//i

};
