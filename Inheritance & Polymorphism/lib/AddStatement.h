#ifndef HW2_ADDSTATEMENT_H
#define HW2_ADDSTATEMENT_H

#include "Statement.h"

class AddStatement: public Statement
{
private:
    string a;
    string b;

public:
    AddStatement(string aa, string bb);

    virtual void execute(ProgramState * state, std::ostream &outf);
};
#endif //HW2_ADDSTATEMENT_H
