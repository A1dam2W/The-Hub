#ifndef HW2_MULTIPLYSTATEMENT_H
#define HW2_MULTIPLYSTATEMENT_H

#include "Statement.h"

class MultiplyStatement: public Statement
{
private:
    string a;
    string b;

public:
    MultiplyStatement(string aa, string bb);

    virtual void execute(ProgramState * state, std::ostream &outf);
};


#endif //HW2_MULTIPLYSTATEMENT_H
