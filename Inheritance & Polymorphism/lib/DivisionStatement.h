#ifndef HW2_DIVISIONSTATEMENT_H
#define HW2_DIVISIONSTATEMENT_H

#include "Statement.h"
#include <string>

class DivisionStatement: public Statement
{
private:
    string a;
    string b;

public:
    DivisionStatement(string aa, string bb);

    virtual void execute(ProgramState * state, std::ostream &outf);
};
#endif //HW2_DIVISIONSTATEMENT_H
