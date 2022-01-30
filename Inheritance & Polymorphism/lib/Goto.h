#ifndef HW2_GOTO_H
#define HW2_GOTO_H
#include "Statement.h"

class Goto: public Statement
{
private:
    int line_num;

public:
    Goto(int a);

    virtual void execute(ProgramState * state, std::ostream &outf);
};
#endif //HW2_GOTO_H
