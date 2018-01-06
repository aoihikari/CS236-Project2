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
#include "Predicate.h"
#include "Parameter.h"

using namespace std;

class Rule {
    
private:

bool predicateList(queue<Token> &tokens, queue<string> &oi){
	bool a = true;	
	bool pl = true;
	if (tokens.front().getName() == "PERIOD"){					
		oi.push(tokens.front().getValue());
		tokens.pop();
	} else {	
		if (tokens.front().getName() == "COMMA"){					
			oi.push(tokens.front().getValue());
			tokens.pop();
			if (predicate(tokens, oi) == true){
				pl = predicateList(tokens, oi);
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
	Predicate predicate_;
	bool a = predicate_.parse(tokens, oi);
		
	return a;
}

bool headPredicate(queue<Token> &tokens, queue<string> &oi){
		
	bool a = true;	
	bool il = true;
	if (tokens.front().getName() == "ID"){
		oi.push(tokens.front().getValue());
		tokens.pop();
		if (tokens.front().getName() == "LEFT_PAREN"){
			oi.push(tokens.front().getValue());
			tokens.pop();
			if (tokens.front().getName() == "ID"){
				oi.push(tokens.front().getValue());
				tokens.pop();
				if (tokens.front().getName() == "RIGHT_PAREN"){
					oi.push(tokens.front().getValue());
					tokens.pop();
				} else {
					il = idList(tokens, oi);
					if (il == true){
					} else {
						a = false;
					}
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

bool rules(queue<Token> &tokens, queue<string> &oi, int &numberr){
	
	bool a = true;
	numberr++;	
	if (headPredicate(tokens, oi) == true){
		if (tokens.front().getName() == "COLON_DASH"){
			oi.push(tokens.front().getValue());
			tokens.pop();
			if (predicate(tokens, oi) == true){
				if (predicateList(tokens, oi) == true){
					oi.push("endl");
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

bool ruleList(queue<Token> &tokens, queue<Token> &oi, queue<string> &oir, int &numberr){
	bool a = true;	
	bool rl = true;
	if (tokens.front().getName() == "QUERIES"){					
		oi.push(tokens.front());
		tokens.pop();
	} else {	
		if (rules(tokens, oir, numberr) == true){
			rl = ruleList(tokens, oi, oir, numberr);
			if (rl == true){
			} else {
				a = false;
			}
		} else {
			a = false;
		}
	}
		
	return a;
}


bool idList(queue<Token> &tokens, queue<string> &oi){
		
	bool a = true;	
	bool il = true;
	if (tokens.front().getName() == "COMMA"){
		oi.push(tokens.front().getValue());
		tokens.pop();
		if (tokens.front().getName() == "ID"){
			oi.push(tokens.front().getValue());
			tokens.pop();
			if (tokens.front().getName() == "RIGHT_PAREN"){
				oi.push(tokens.front().getValue());
				tokens.pop();
			} else {
				il = idList(tokens, oi);
				if (il == true){
					
				} else {
					a = false;
				}
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
    
Rule (){}

bool parse(queue<Token> &tokens, queue<Token> &oi, queue<string> &oir, int &numberr){
	bool a = true;
	bool rl = true;
		
	rl = ruleList(tokens, oi, oir, numberr);
	if (rl == true){
		
	} else {
		a = false;
	}	
	return a;	

}	

	~Rule(){}
    
};
