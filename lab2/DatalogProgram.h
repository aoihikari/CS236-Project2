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
#include "Rule.h"
#include <set>

using namespace std;

class DatalogProgram {
    
private:

bool queryList(queue<Token> &tokens, queue<string> &oiq, int &numberq){
	bool a = true;	
	bool ql = true;
	if (tokens.front().getName() != "EOF"){					
		if (queries(tokens, oiq, numberq) == true){
			ql = queryList(tokens, oiq, numberq);
			if (ql == true){
			} else {
				a = false;
			}
		} else {
			a = false;
		}
	} else {
	}		
	return a;
}

bool queries(queue<Token> &tokens, queue<string> &oiq, int &numberq){
	
	bool a = true;	
	numberq++;
	if (predicate(tokens, oiq) == true){
			if (tokens.front().getName() == "Q_MARK"){
				oiq.push(tokens.front().getValue());
				tokens.pop();
				oiq.push("endl");
			} else {
				a = false;
			}
	} else {
		a = false;
	}
		
	return a;
}

bool predicate(queue<Token> &tokens, queue<string> &oi){
		
	Predicate predicate_;
	bool a = predicate_.parse(tokens, oi);
		
		
	return a;
}
bool ruleList(queue<Token> &tokens, queue<Token> &oi, queue<string> &oir, int &numberr){
	Rule ola;
	bool rl = ola.parse(tokens, oi, oir, numberr);
	return rl;
}

bool stringList(queue<Token> &tokens, queue<string> &oi, set<string> &domain, int &domainn){
		
	bool a = true;	
	bool sl = true;
	if (tokens.front().getName() == "COMMA"){
		oi.push(tokens.front().getValue());
		tokens.pop();
		if (tokens.front().getName() == "STRING"){
			oi.push(tokens.front().getValue());
			domain.insert(tokens.front().getValue());
			domainn++;
			tokens.pop();
			if (tokens.front().getName() == "RIGHT_PAREN"){
				oi.push(tokens.front().getValue());
				tokens.pop();
				if (tokens.front().getName() == "PERIOD"){
					oi.push(tokens.front().getValue());
					tokens.pop();
				} else {
					 a = false;
				}
			} else {
				sl = stringList(tokens, oi, domain, domainn);
				if (sl == true){
					
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

bool facts(queue<Token> &tokens, queue<string> &oif, int &numberf, set<string> &domain, int &domainn){
	
	bool a = true;	
	bool sl = true;
	numberf++;
	if (tokens.front().getName() == "ID"){
			oif.push(tokens.front().getValue());
			tokens.pop();	
			if (tokens.front().getName() == "LEFT_PAREN"){
				oif.push(tokens.front().getValue());
				tokens.pop();
				if (tokens.front().getName() == "STRING"){
					oif.push(tokens.front().getValue());
					domain.insert(tokens.front().getValue());
					domainn++;
					tokens.pop();
					if (tokens.front().getName() == "RIGHT_PAREN"){
						oif.push(tokens.front().getValue());
						tokens.pop();
						if (tokens.front().getName() == "PERIOD"){
							oif.push(tokens.front().getValue());
							tokens.pop();
							oif.push("endl");
						} else {
						 a = false;
						}
					} else {
						sl = stringList(tokens, oif, domain, domainn);
						if (sl == true){
							oif.push("endl");
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

bool factList(queue<Token> &tokens, queue<Token> &oi, queue<string> &oif, int &numberf, set<string> &domain, int &domainn){
	bool a = true;	
	bool fl = true;
	if (tokens.front().getName() == "RULES"){					
		oi.push(tokens.front());
		tokens.pop();
	} else {	
		if (facts(tokens, oif, numberf, domain, domainn) == true){
			fl = factList(tokens, oi, oif, numberf, domain, domainn);
			if (fl == true){
			} else {
				a = false;
			}
		} else {
			a = false;
		}
	}
		
	return a;
}

bool schemeList(queue<Token> &tokens, queue<Token> &oi, queue<string> &ois,int &numbers){
	bool a = true;	
	bool sl = true;
	if (tokens.front().getName() == "FACTS"){					
		oi.push(tokens.front());
		tokens.pop();
	} else {	
		if (schemes(tokens, ois, numbers) == true){
			sl = schemeList(tokens, oi, ois, numbers);
			if (sl == true){
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

bool schemes(queue<Token> &tokens, queue<string> &ois, int &numbers){
	
	bool a = true;	
	bool il = true;
	numbers++;
	if (tokens.front().getName() == "ID"){
			ois.push(tokens.front().getValue());
			tokens.pop();	
			if (tokens.front().getName() == "LEFT_PAREN"){
				ois.push(tokens.front().getValue());
				tokens.pop();
				if (tokens.front().getName() == "ID"){
					ois.push(tokens.front().getValue());
					tokens.pop();
					if (tokens.front().getName() == "RIGHT_PAREN"){
						ois.push(tokens.front().getValue());
						tokens.pop();
						ois.push("endl");
					} else {
						il = idList(tokens, ois);
						if (il == true){
							ois.push("endl");
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

string toStringf(queue<Token> &tokens)
{
	stringstream ss;
	ss << "Failure!"<<endl;
	ss << "  ("<< tokens.front().getName()<< ",\""<<tokens.front().getValue()<<"\","<<tokens.front().getLine()<<")"<<endl;
	return ss.str();
}
void domainf(int &domainn, set<string> &domain, stringstream &ss){
	set<string>::iterator iter;
	domainn = 0;
	for(iter=domain.begin(); iter!=domain.end();++iter) {
		domainn++;
	}
	ss << "Domain("<< domainn<<"):"<< endl;
	
	for(iter=domain.begin(); iter!=domain.end();++iter) {
		ss << "  ";		
		ss << *iter<<endl;
	}
}
void queriesf(stringstream &ss,int &numberq, queue<Token> &oi, queue<string> &oiq){			
	ss << "("<< numberq<< ")";
	oi.pop();
	ss << oi.front().getValue()<< endl;
	if (numberq != 0)
	ss << "  ";
	for (unsigned i=0; i< oiq.size(); i++){
		if (oiq.front() == "endl"){
			ss << endl;
			if (oiq.size() != 1)
				ss << "  ";
		} else {				
			ss << oiq.front();
		}
		oiq.pop();
		i--;
	}
}
void rulesf(stringstream &ss,int &numberr, queue<Token> &oi, queue<string> &oir){			
	ss << "("<< numberr<< ")";
	oi.pop();
	ss << oi.front().getValue()<< endl;
	if (numberr != 0)
	ss << "  ";
	for (unsigned i=0; i< oir.size(); i++){
		if (oir.front() == "endl"){
			ss << endl;
			if (oir.size() != 1)
				ss << "  ";
		} else if (oir.front() == ":-") {
			ss << " "<<oir.front()<< " ";
		} else {				
			ss << oir.front();
		}
		oir.pop();
		i--;
	}
}

void factsf(stringstream &ss,int &numberf, queue<Token> &oi, queue<string> &oif){			
	ss << "("<< numberf<< ")";
	oi.pop();
	ss << oi.front().getValue()<< endl;
	if (numberf != 0)
	ss << "  ";
	for (unsigned i=0; i< oif.size(); i++){
		if (oif.front() == "endl"){
			ss << endl;
			if (oif.size() != 1)
				ss << "  ";
		} else {				
			ss << oif.front();
		}
		oif.pop();
		i--;
	}
}

void factss(stringstream &ss,int &numbers, queue<Token> &oi, queue<string> &ois){			
	ss << "("<< numbers<< ")";
	oi.pop();
	ss << oi.front().getValue()<< endl;
	if (numbers != 0)
		ss << "  ";
		for (unsigned i=0; i< ois.size(); i++){
			if (ois.front() == "endl"){
				ss << endl;
				if (ois.size() != 1)
					ss << "  ";
			} else {				
				ss << ois.front();
			}
			ois.pop();
			i--;
		}
}

string toStringt(queue<Token> oi, queue<string> ois, queue<string> oif, queue<string> oir, queue<string> oiq, int &numbers, int &numberf,int &numberr,int &numberq, set<string> &domain, int &domainn)
{
	stringstream ss;
	ss << "Success!"<<endl;
	for (unsigned i=0; i< oi.size(); i++){
	
		ss << oi.front().getValue();
		if (oi.front().getName() == "SCHEMES"){
			factss(ss, numbers, oi, ois);
		} else if (oi.front().getName() == "FACTS"){
			factsf(ss,numberf, oi, oif);

		} else if (oi.front().getName() == "RULES"){
			rulesf(ss,numberr,oi,oir);			
			
		} else {
			queriesf(ss, numberq, oi, oiq);			
						
		}
		oi.pop();
		i--;
	
	}
	domainf(domainn, domain, ss);
	
	return ss.str();
}
void parse2(bool fl, queue<Token> &tokens, queue<Token> &oi, bool rl, bool q, bool ql, bool &a, queue<string> &oir, queue<string> &oiq, int &numberr, int &numberq){   
if (fl == true){
	if (tokens.front().getName() == "COLON"){
		oi.push(tokens.front());
		tokens.pop();
		rl = ruleList(tokens, oi, oir, numberr);
		if (rl == true){
			if (tokens.front().getName() == "COLON"){
				oi.push(tokens.front());
				tokens.pop();
				q = queries(tokens, oiq, numberq);
				if (q == true){
					ql = queryList(tokens, oiq, numberq);
					if (ql == true){
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
} else {
	a = false;
}
}  
    
void eraseComment(queue<Token> &tokens, queue<Token> oi){
for (unsigned i = 0; i < tokens.size(); i++){
	if (tokens.front().getName() == "COMMENT"){
		tokens.pop();
		i--;
	} else {
		oi.push(tokens.front());
		tokens.pop();
		i--;
	}
}
for (unsigned i = 0; i < oi.size(); i++){
		
	tokens.push(oi.front());
	oi.pop();
	i--;
}
}

public:
    
DatalogProgram (){}

void parse(queue<Token> &tokens){
	queue<string> ois;
	queue<string> oif;
	queue<string> oir;
	queue<string> oiq;
	queue<Token> oi;
	set<string> domain;
	int domainn = 0;
	bool a = true;	
	bool s = true;
	bool sl = true;
	bool fl = true;
	bool rl = true;
	bool q = true;
	bool ql = true;
	int numbers = 0;
	int numberf = 0;
	int numberr = 0;
	int numberq = 0;
	

	eraseComment(tokens,oi);
	
	if (tokens.front().getName() == "SCHEMES"){
		oi.push(tokens.front());
		tokens.pop();
		if (tokens.front().getName() == "COLON"){
			oi.push(tokens.front());
			tokens.pop();
			s = schemes(tokens, ois, numbers);
			if (s == true){
				sl = schemeList(tokens, oi, ois, numbers);
				if (sl == true){
					if (tokens.front().getName() == "COLON"){
						oi.push(tokens.front());
						tokens.pop();
						fl = factList(tokens, oi, oif, numberf, domain, domainn);
						parse2(fl, tokens, oi, rl, q, ql, a, oir, oiq, numberr, numberq);
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
	
	if ( a == false){
		cout << toStringf(tokens);
	} else {
		cout << toStringt(oi, ois,oif,oir,oiq, numbers, numberf, numberr, numberq, domain, domainn);
	}	

}	

	~DatalogProgram(){}
    
};
