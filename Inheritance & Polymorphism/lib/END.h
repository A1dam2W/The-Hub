#ifndef HW2_END_H
#define HW2_END_H
#include "Statement.h"

class END: public Statement
{
public:
    END();

    virtual void execute(ProgramState * state, std::ostream &outf);
};
#endif //HW2_END_H
