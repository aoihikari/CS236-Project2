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
#include "Parameter.h"

using namespace std;

class Predicate {
    
private:

bool parameterList(queue<Token> &tokens, queue<string> &oi){
	bool a = true;	
	bool pl = true;
	if (tokens.front().getName() == "RIGHT_PAREN"){					
		oi.push(tokens.front().getValue());
		tokens.pop();
	} else {	
		if (tokens.front().getName() == "COMMA"){					
			oi.push(tokens.front().getValue());
			tokens.pop();
			if (parameter(tokens, oi) == true){
				pl = parameterList(tokens, oi);
				if (pl == true){
				} else {
					a = false;
				}
			} else {
				a = false;
			}
		} else {
			a = false;
		}
	}
		
	return a;
}

bool parameter(queue<Token> &tokens, queue<string> &oi){
	Parameter parameter_;	
	bool a = parameter_.parse(tokens, oi);
		
	return a;
}

bool predicate(queue<Token> &tokens, queue<string> &oi){
		
	bool a = true;	
	bool p = true;
	if (tokens.front().getName() == "ID"){
		oi.push(tokens.front().getValue());
		tokens.pop();
		if (tokens.front().getName() == "LEFT_PAREN"){
			oi.push(tokens.front().getValue());
			tokens.pop();
			p = parameter(tokens, oi);			
			if (p == true){
				if (parameterList(tokens, oi) == true){
						
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

   
public:
    
Predicate (){}

bool parse(queue<Token> &tokens, queue<string> &oi){
	bool a = true;
	bool p = true;
	
	p = predicate(tokens, oi);
	if (p == true){
		
	} else {
		a = false;
	}	
	return a;	

}	

	~Predicate(){}
    
};
