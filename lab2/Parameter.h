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
#include <sstream>

using namespace std;

class Parameter {
    
private:

bool expression(queue<Token> &tokens, queue<string> &oi){
		
	bool a = true;	
	bool p = true;
	if (tokens.front().getName() == "LEFT_PAREN"){
		oi.push(tokens.front().getValue());
		tokens.pop();
		p = parameter(tokens, oi);			
		if (p == true){
			if (tokens.front().getName() == "ADD" || tokens.front().getName() == "MULTIPLY"){
				oi.push(tokens.front().getValue());
				tokens.pop();
				p = parameter(tokens, oi);			
				if (p == true){
					if (tokens.front().getName() == "RIGHT_PAREN"){
						oi.push(tokens.front().getValue());
						tokens.pop();
					} else {
						a = false;
					}
				} else {
					a = false;
				}	
			} else {
				a = false;
			}
				
		} else {
			a = false;
		}	
		
	} else {
		a = false;
	}
		
	return a;
}


bool parameter(queue<Token> &tokens, queue<string> &oi){
		
	bool a = true;	
	if (tokens.front().getName() == "STRING" || tokens.front().getName() == "ID"){
		oi.push(tokens.front().getValue());
		tokens.pop();
	} else {
		if (expression(tokens, oi) ==true){
		} else {
			a = false;
		}
	}
		
	return a;
}
   
public:
    
Parameter (){}

bool parse(queue<Token> &tokens, queue<string> &oi){
	bool a = true;
	bool p = true;
	
	p = parameter(tokens, oi);
	if (p == true){
		
	} else {
		a = false;
	}	
	return a;	

}	

	~Parameter(){}
    
};
