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
#include "Lexier.h"
#include "DatalogProgram.h"

using namespace std;


int main(int argc, char* argv[]) {

	//Enter file name

	ifstream in_file;
	in_file.open(argv[1]);
	queue<Token> tokens;
	Lexier existtokens;
	DatalogProgram w;
	//bool a;
	
	if (in_file.fail())
	{
		cout << "\nCouldn't load file\n\n" << endl;
		return 0;
	}
	else {
				
		existtokens.getTokens(in_file,tokens);		
		
		w.parse(tokens);
		
		in_file.close();
	}
	return 0;
}

//---------------------------------------------------------------------------------------
