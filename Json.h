# pragma once
#include<string>
#include<fstream>
#include<iostream>
#include <vector>
#include "HashMap.h"
#include <sstream>

enum class Type {
	String,
	Number,
	Array,
	Null,
	Boolean,
	OpennningBracket,
	ClosingBracket,
	Dots,
	Comma
};

struct Token
{
	Type type;
	Token();
	explicit Token(const Type type);
	virtual void print(std::ostream& out) const;


};

struct StringToken : public Token
{
	std::string data;
	explicit StringToken(const std::string& data);

	void print(std::ostream& out) const override;
};

struct ArrayToken : public Token
{
	std::vector<Token*> arrayData;
	explicit ArrayToken(const std::vector<Token*>& arrayData);

	void print(std::ostream& out) const override;
};

struct BooleanToken : public Token
{
	bool data;
	explicit BooleanToken(const bool data);

	void print(std::ostream& out) const override;
};

struct NumberToken : public Token
{
	double num;
	explicit NumberToken(const double num);

	void print(std::ostream& out) const override;
};
class Json
{
public:
	
	Json();
	void makeTokens(std::vector<Token*>& tokens);
	//void makeTokensWith(std::vector<Token*>& tokens);
	void print();
	bool read(const std::string& fileName);
	bool isAlpha(char c);
	std::string eatString(size_t idx, const std::string& str);

private:

	std::string content;


	/*?
{"name":"John","age":30,"isMarrued":false,"hobbies":["swimming","tennis"],"humour":null}

[Token:openning_bracket, Token:String(name), Token:dots, Token:String(John)]*/

};