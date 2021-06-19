#include "Json.h"



Token::Token()
{
	this->type = Type::Null;
}

Token::Token(const Type type)
{
    this->type = type;
}

void Token::print(std::ostream& out) const
{
	switch (type)
	{
	case Type::String:
	{
		out << "String";
		break;
	}
	case Type::Boolean:
	{
		out << "Boolean";
		break;
	}
	case Type::OpennningBracket:
	{
		out << "OpennningBracket";
		break;
	}
	case Type::ClosingBracket:
	{
		out << "ClosingBracket";
		break;
	}
	case Type::Dots:
	{
		out << "Dots";
		break;
	}
	case Type::Comma:
	{
		out << "Comma";
		break;
	}
	case Type::Number:
	{
		out << "Number";
		break;
	}
	case Type::Array:
	{
		out << "Array";
		break;
	}
	case Type::Null:
	{
		out << "Null";
		break;
	}
	default:
		out << "Wrong";
	}
	out<< " ";
}

StringToken::StringToken(const std::string& data) : Token(Type::String)
{
	
	this->data = data;
}
void StringToken::print(std::ostream& out) const
{
	Token::print(out);
	out << ':' << data;
	out << " ";
}

ArrayToken::ArrayToken(const std::vector<Token*>& arrayData) : Token(Type::Array)
{
	unsigned size = arrayData.size();
	for (size_t i = 0; i < size; i++)
	{
		this->arrayData[i] = arrayData[i];
	}
}
void ArrayToken::print(std::ostream& out) const
{
	unsigned size = arrayData.size();
	
	Token::print(out);
	for (int i = 0; i < size; ++i)

		arrayData[i]->print(out);
	out << " ";
}    

BooleanToken::BooleanToken(const bool data) : Token(Type::Boolean)
{

	this->data = data;
}
void BooleanToken::print(std::ostream& out) const 
{
	Token::print(out);
	out << ':' << data;
	out << " ";
}
NumberToken::NumberToken(const double num) : Token(Type::Number)
{
	this->num = num;
}
void NumberToken::print(std::ostream& out) const
{
	Token::print(out);
	out << ':' << num;
	out << " ";
}

Json::Json()
{
	this->content = "";
}
/*

bool Json::isAlpha(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
std::string Json::eatString(size_t idx, const std::string& str)
{
	size_t sizeString = str.size();
	std::string result;
	
	if (idx <0 || idx >= str.size())
	{
		return std::string();
	}
	for (size_t i = 0; i < sizeString, isAlpha(str[i]); i++)
	{
		result += str[i];
		
	}
	return result;
} */
void Json::makeTokens(std::vector<Token*>& tokens)
{
	unsigned size = content.size();
	for (int i = 0; i < size; ++i)
	{
		if (content[i] == '{')
		{
			tokens.push_back(new Token(Type::OpennningBracket));
		}
		else if (content[i] == '"')
		{
			std::string key;
			++i;
			while (content[i] != '"')
			{
				key += content[i];
				++i;
			}
			tokens.push_back(new StringToken(key));
		}
		else if (content[i] == ':')
		{
			tokens.push_back(new Token(Type::Dots));
		}
		else if (content[i] == ',')
		{
			tokens.push_back(new Token(Type::Comma));
		}
		else if (content[i] == '}')
		{
			tokens.push_back(new Token(Type::ClosingBracket));
		}
		else if (content[i] == 'n')
		{
			
			tokens.push_back(new Token(Type::Null));
			i += 3;
		}
		else if (content[i] >= '0' && content[i] <= '9')
		{
			unsigned number = 0;
			
			do
			{
				
				number = number * 10 + (content[i] - '0');
				++i;

			} while (content[i] >= '0' && content[i] <= '9');
			
			tokens.push_back(new NumberToken(number));

		}
		else if (content[i] == 't')
		{
			tokens.push_back(new BooleanToken(true));
			i += 3;
		}
		else if (content[i] == 'f')
		{
			tokens.push_back(new BooleanToken(false));
			i += 4;
		}
		else if (content[i] == '[')
		{

			ArrayToken array({});
			++i;
			while (content[i] != ']')
			{

				std::string toInsert;
				while (content[i] != ',' && content[i] != ']' && content[i] != ' ')
				{
					toInsert += content[i];
					++i;

				}
				switch (toInsert[0])
				{
				case 'n': {
					array.arrayData.push_back(new Token(Type::Null));
					i += 3;
					break;

				}
				case't': {
					array.arrayData.push_back(new BooleanToken(true));
					i += 3; break; }
				case'f': {
					array.arrayData.push_back(new BooleanToken(false));
					i += 4; break; }
				case'"': {

					array.arrayData.push_back(new StringToken(toInsert.substr(1, toInsert.length() - 2)));
					//i += 2;
					break; }
				case '0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9': {
					unsigned number = 0;
					do
					{
						number = number * 10 + (content[i] - '0');
						++i;
					} while (content[i] >= '0' && content[i] <= '9');
					array.arrayData.push_back(new NumberToken(number)); break; }
				case ']': {break; }
				default:
					++i;

				}



			}
			tokens.push_back(new ArrayToken(array));


		}
	}
}
/*
void Json::makeTokensWith(std::vector<Token*>& tokens)
{
	unsigned size = content.size();
	for (int i = 0; i < size; ++i)
	{
		if (content[i] == '{')
		{
			tokens.push_back(new Token(Type::OpennningBracket));
		}
		else if (content[i] == '"')
		{
			std::string key;
			++i;
			while (content[i] != '"')
			{
				key += content[i];
				++i;
			}
			tokens.push_back(new StringToken(key));
		}
		else if (content[i] == ':')
		{
			tokens.push_back(new Token(Type::Dots));
		}
		else if (content[i] == ',')
		{
			tokens.push_back(new Token(Type::Comma));
		}
		else if (content[i] == '}')
		{
			tokens.push_back(new Token(Type::ClosingBracket));
		}
		else if (content[i] == 'n')
		{
		//else if (isAlfa(content[i]) {
			//string word = eatString(i, content);

		//}
			tokens.push_back(new Token(Type::Null));
			i += 3;
		}
		else if (content[i] >= '0' && content[i] <= '9')
		{
			unsigned number = 0;
			std::stringstream ss;
			ss << content[i];
			do
			{
				ss << content[i];
				//number = number * 10 + (content[i] - '0');
				++i;

			} while (content[i] >= '0' && content[i] <= '9' && content.size() > i);
			ss >> number;
			tokens.push_back(new NumberToken(number));

		}
		else if (content[i] == 't')
		{
			tokens.push_back(new BooleanToken(true));
			i += 3;
		}
		else if (content[i] == 'f')
		{
			tokens.push_back(new BooleanToken(false));
			i += 4;
		}
		else if (content[i] == '[')
		{

			ArrayToken array({});
			++i;
			while (content[i] != ']')
			{
				
				std::string toInsert;
				while (content[i] != ',' &&  content[i] != ']' && content[i] != ' ')
				{
					toInsert += content[i];
					++i;

				}
				switch (toInsert[0])
				{
				case 'n': {
					array.arrayData.push_back(new Token(Type::Null));
					i += 3;
					break;

				}
				case't': {
					array.arrayData.push_back(new BooleanToken(true));
					i += 3; break; }
				case'f': {
					array.arrayData.push_back( new BooleanToken(false));
					i += 4; break; }
				case'"': {
				
					array.arrayData.push_back(new StringToken(toInsert.substr(1, toInsert.length() - 2)));
					//i += 2;
					break; }
				case '0' || '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9': {
					unsigned number = 0;
					do
					{
						number = number * 10 + (content[i] - '0');
						++i;
					} while (content[i] >= '0' && content[i] <= '9');
					array.arrayData.push_back(new NumberToken(number)); break; }
				case ']': {break; }
				default:
					++i;
				
				}
				


			}
			tokens.push_back(new ArrayToken(array));


		}
	}
} */

void Json::print()
{
	std::cout << content;
}

bool Json::read(const std::string& fileName)
{
	std::ifstream fileInput(fileName);
	if (!fileInput)
	{
		return false;
	}
	while (fileInput)
	{
		char c;
		fileInput.get(c);
		if (fileInput)
		{
			content += c;
		}
		
	}
	return true;
	return false;
}
