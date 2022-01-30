// Interpreter.cpp
#include "Statement.h"
#include "LetStatement.h"
#include "PrintStatement.h"
#include "PrintAllStatement.h"
#include "AddStatement.h"
#include "SubtractStatement.h"
#include "MultiplyStatement.h"
#include "DivisionStatement.h"
#include "IfStatement.h"
#include "Goto.h"
#include "END.h"
#include "GOSUB.h"
#include "RETURN.h"
#include "dotend.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>

using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);

int main()
{
        cout << "Enter BASIC program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile)
        {
                cout << "Cannot open " << filename << "!" << endl;
                return 1;
        }
        interpretProgram(infile, cout);
}



void parseProgram(istream &inf, vector<Statement *> & program)
{
	program.push_back(NULL);
	
	string line;
	while( ! inf.eof() )
	{
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}


Statement * parseLine(string line)
{
	Statement * statement;	
	stringstream ss;
	string type;
	string var;
	int val;
    int dummy;

	ss << line;
    ss >> dummy;
	ss >> type;
	
	if ( type == "LET" )
	{
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);
	}
    if ( type == "PRINT")
    {
        ss >> var;
        statement = new PrintStatement(var);
    }
    if ( type == "PRINTALL")
    {
        statement = new PrintAllStatement();
    }
    if ( type == "ADD")
    {
        ss >> var;
        string var2;
        ss >> var2;
        statement = new AddStatement(var, var2);
    }
    if ( type == "SUB")
    {
        ss >> var;
        string var2;
        ss >> var2;
        statement = new SubtractStatement(var, var2);
    }
    if ( type == "MULT")
    {
        ss >> var;
        string var2;
        ss >> var2;
        statement = new MultiplyStatement(var, var2);
    }
    if ( type == "DIV")
    {
        ss >> var;
        string var2;
        ss >> var2;
        statement = new DivisionStatement(var, var2);
    }
    if ( type == "IF")
    {
        ss >> var;
        string opr;
        string then;
        int line_num;
        ss >> opr;
        ss >> val;
        ss >> then;
        ss >> line_num;
        statement = new IfStatement(var, opr, val, line_num);
    }
    if (type == "GOTO")
    {
        ss >> val;
        statement = new Goto(val);
    }
    if(type == "GOSUB")
    {
        ss >> val;
        statement = new GOSUB(val);
    }
    if (type == "END"){
        statement = new END();
    }
    if (type == "."){
        statement = new dotend();
    }
    if(type == "RETURN"){
        statement = new RETURN();
    }
    return statement;
}


void interpretProgram(istream& inf, ostream& outf) {
    vector<Statement *> program;
    parseProgram( inf, program );
    int programsize = program.size();
    ProgramState* input = new ProgramState(programsize);
    while(program[input->getline()] !=  nullptr){//initially pushed back a nullptr, program should terminate after hitting the nullptr
        program[input->getline()]->execute(input, outf);
    }
    for (unsigned int i = 0; i < program.size(); i++) {
        delete program[i];
    }
    delete input;
}
