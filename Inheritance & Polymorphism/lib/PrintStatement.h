#ifndef PRINT_STATEMENT_INCLUDED
#define PRINT_STATEMENT_INCLUDED

#include "Statement.h"

class PrintStatement: public Statement
{
private:
    string m_variableName;

public:
    PrintStatement(string variableName);

    virtual void execute(ProgramState * state, ostream &outf);
};

#endif
