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

class Token {
    
private:
    
    string name;
    
    string value;
    
    unsigned line;
    
public:
    
    Token (string n, string v, int l): name(n), value(v), line(l){}

    const string getName() { return name; }
    
    const string getValue() { return value; }
    
    const unsigned getLine() { return line; }

	~Token(){}
    
};
