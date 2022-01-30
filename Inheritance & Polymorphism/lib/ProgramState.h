// ProgramState.h
//
// CS 104 / Fall 2021
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a BASIC program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// We've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.
#include <map>
#include <stack>

using namespace std;

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

class ProgramState
{
public:
	ProgramState(int numLines);//the program counter that needs to be incremented
    ~ProgramState();
    void nextline();
    int getline();
    bool isfound(std::string s);
    void insert(std::string s, int value);
    void addition(std::string a, std::string b);
    void subtraction(std::string a, std::string b);
    void division(std::string a, std::string b);
    void multiplication(std::string a, std::string b);
    int getval(std::string s);
    void setval(std::string s, int val);
    void Goto(int linenumber);
    bool ifcompare(std::string var_name, std::string opr, int val);
    void GOSUB(int jumpline);
    int poptop();
    bool isempty();
    void endofprogram();
    void printall();

	// You'll need to add a variety of methods here.  Rather than trying to
	// think of what you'll need to add ahead of time, add them as you find
	// that you need them.


private:
	int m_numLines;
    int max_lines;
    map <std::string, int> variable;
    stack <int> sta;
};

#endif
