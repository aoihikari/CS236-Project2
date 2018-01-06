#pragma once
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <locale>
#include <ctype.h>
#include "Token.h"
#include <queue>

using namespace std;

class Lexier {
    
private:
    
//---------------------------------------------------------------------------------------
void ponctuation(string &letra, map<string, string> symbols, ifstream &in_file, int count, int &count2, queue<Token> &tokens) {

	if (letra == ":") {
		string copy = letra;
		letra = in_file.peek();
		if (letra == "-") {
			copy += in_file.get();
			Token token("COLON_DASH", copy , count);
			tokens.push(token);
			count2++;
		}
		else {
			Token token(symbols[copy], copy , count);
			tokens.push(token);			
			count2++;
		}
	}
	else {
		Token token(symbols[letra], letra , count);
		tokens.push(token);		
		count2++;
	}
}
//---------------------------------------------------------------------------------------
void read_filep(ifstream &in_file, int &count, int &count2, map<string, string>symbols, string &letra, queue<Token> &tokens) {
	ponctuation(letra, symbols, in_file, count, count2, tokens);
}
//---------------------------------------------------------------------------------------
void string_state2(string &letra, string &palavra, ifstream &in_file, string &temp, int &count) {
	if (letra == "'") {
		temp = letra;
		letra = in_file.peek();
		if (letra == "'") {
			letra = in_file.get();
			temp += letra;
			palavra += temp;
			temp = "";
		}
		else {
			palavra += temp;
		}
	}
	else {
		if (letra == "\n") {
			count++;
		}
		palavra += letra;
	}
}
//---------------------------------------------------------------------------------------
void string_state(string &letra, ifstream &in_file, int &count, int &count2, queue<Token> &tokens) {

	string palavra = letra;
	string temp;
	int startstr = count;
	while (temp != "'" && in_file.peek() != EOF) {
		letra = in_file.get();
		string_state2(letra, palavra, in_file, temp, count);
	}

	if (in_file.peek() != EOF) {
		Token token("STRING", palavra, startstr);
		tokens.push(token);		
	}
	else {
		if (temp == "'") {
			Token token("STRING", palavra, startstr);
			tokens.push(token);				
		}
		else {
			Token token("UNDEFINED", palavra, startstr);
			tokens.push(token);				
		}
	}
	count2++;
	
}
//---------------------------------------------------------------------------------------
void comment2(string &letra, ifstream &in_file, string &palavra, int &count, int &startcom) {
	string temp;
	while (temp != "|" && in_file.peek() != EOF) {
		letra = in_file.get();
		palavra += letra;
		letra = in_file.peek();
		if (letra == "\n") {
			count++;
		}
		temp = letra;
	}
	temp = "";
	if (letra == "|") {
		while (temp != "#" && in_file.peek() != EOF) {
			letra = in_file.get();
			palavra += letra;
			letra = in_file.peek();
			if (letra == "\n") {
				count++;
			}
			temp = letra;
		}
	}

}
//---------------------------------------------------------------------------------------
void comment3(string &letra, ifstream &in_file, string &palavra) {
	while (letra != "\n") {
		if (letra =="\r"){
			letra = in_file.get();
			letra = in_file.peek();
		} else {
			letra = in_file.get();
			palavra += letra;
			letra = in_file.peek();
		}
	}
}
//---------------------------------------------------------------------------------------
void comment(string &letra, ifstream &in_file, int &count, int &count2, queue<Token> &tokens) {

	string palavra = letra;
	int startcom = count;
	letra = in_file.peek();
	if (letra == "|") {
		comment2(letra, in_file, palavra, count, startcom);
		if (!in_file.good()) {
			if (letra == "#") {
				letra = in_file.get();
				palavra += letra;
				Token token("COMMENT", palavra, startcom);
				tokens.push(token);				
			}
			else {
				Token token("UNDEFINED", palavra, startcom);
				tokens.push(token);				
			}
		}
		else {
			letra = in_file.get();
			palavra += letra;
			Token token("COMMENT", palavra, startcom);
			tokens.push(token);
		}
	}
	else {
		comment3(letra, in_file, palavra);
		Token token("COMMENT", palavra, count);
		tokens.push(token);
	}
	count2++;
}
//---------------------------------------------------------------------------------------
void read_file2(string &letra, ifstream &in_file, int &count, int &count2, map <string, string> keys, queue<Token> &tokens) {
	string palavra = letra;
	letra = in_file.peek();
	string temp = letra;
	while (isalpha(temp[0])) {
		letra = in_file.get();
		palavra += letra;
		letra = in_file.peek();
		temp = letra;
	}
	if (keys.count(palavra) > 0) {
		Token token(keys[palavra], palavra , count);
		tokens.push(token);
		count2++;
	}
	else {
		while (isalpha(temp[0]) || isdigit(temp[0])) {
			letra = in_file.get();
			palavra += letra;
			letra = in_file.peek();
			temp = letra;
		} 
		Token token("ID", palavra, count);
		tokens.push(token);		
		count2++;
	}
}
//---------------------------------------------------------------------------------------

void read_file(ifstream &in_file, int &count, int &count2, queue<Token> &tokens) {

	map<string, string> symbols = {
		{ ".", "PERIOD" },
		{ ",", "COMMA" },
		{ "?", "Q_MARK" },
		{ "(", "LEFT_PAREN" },
		{ ")", "RIGHT_PAREN" },
		{ ":", "COLON" },
		{ ":-", "COLON_DASH" },
		{ "*", "MULTIPLY" },
		{ "+", "ADD" },
	};

	map<string, string> keys = {
		{ "Schemes", "SCHEMES" },
		{ "Facts", "FACTS" },
		{ "Rules", "RULES" },
		{ "Queries", "QUERIES" },
	};

	string palavra = "";
	string letra;
	letra = in_file.get();

		if (symbols.count(letra) > 0) {
			read_filep(in_file, count, count2,symbols, letra, tokens);
		}
		else if (letra == "\n") {
			count++;
		}
		else if (letra == "\r") {
			
		}
		else if (letra == "'") {
			string_state(letra, in_file, count, count2, tokens);
		}
		else if (letra == "#") {
			comment(letra, in_file, count, count2, tokens);
		}
		else if (isalpha(letra[0])) {
			read_file2(letra, in_file, count, count2, keys, tokens);
		}
		else {
			if (!isspace(letra[0])) {
				Token token("UNDEFINED", letra, count);
				tokens.push(token);
				count2++;
			}
		}
}
//---------------------------------------------------------------------------------------
	public:
Lexier (){}

void getTokens(ifstream &in_file, queue<Token> &tokens_) {

	//Enter file name

	int count2 = 0;
	int count = 1;
	queue<Token> tokens;
	
		while (in_file.peek() != EOF)
		{
			read_file(in_file, count, count2, tokens);
		}
		Token token("EOF", "", count-1);
		tokens.push(token);		
		count2++;
		for (unsigned i=0; i<tokens.size(); i++){	
			
			tokens_.push(tokens.front());
			tokens.pop();
			i--;
		}
}

//---------------------------------------------------------------------------------------
	~Lexier(){}
    
};
