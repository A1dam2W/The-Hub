#ifndef HW2_IFSTATEMENT_H
#define HW2_IFSTATEMENT_H

#include "Statement.h"
#include "ProgramState.h"

class IfStatement: public Statement
{
private:
    string var_name;
    string opr;
    int val;
    int line;
public:
    IfStatement(string var_name, string opr, int val, int line);

    virtual void execute(ProgramState * state, std::ostream &outf);
};
#endif //HW2_IFSTATEMENT_H
