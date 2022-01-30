#ifndef HW2_SUBTRACTSTATEMENT_H
#define HW2_SUBTRACTSTATEMENT_H

#include "Statement.h"

class SubtractStatement: public Statement
{
private:
    string a;
    string b;

public:
    SubtractStatement(string aa, string bb);

    virtual void execute(ProgramState * state, std::ostream &outf);
};
#endif //HW2_SUBTRACTSTATEMENT_H
