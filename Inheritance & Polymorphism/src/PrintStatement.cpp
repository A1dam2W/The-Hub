// PrintStatement.cpp:
#include "PrintStatement.h"

using namespace std;

PrintStatement::PrintStatement(string variableName) : m_variableName(variableName) {}

void PrintStatement::execute(ProgramState* state, ostream& outf) {
    outf << state->getval(m_variableName) << endl;
    state->nextline();
}
