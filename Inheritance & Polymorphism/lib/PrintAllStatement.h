#ifndef HW2_PRINTALLSTATEMENT_H
#define HW2_PRINTALLSTATEMENT_H

#include "Statement.h"

class PrintAllStatement: public Statement
{
public:
    PrintAllStatement();
    virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif //HW2_PRINTALLSTATEMENT_H
