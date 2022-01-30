#ifndef HW2_GOSUB_H
#define HW2_GOSUB_H

#include "Statement.h"

class GOSUB:public Statement
{
private:
    int line_num;

public:
    GOSUB(int line);
    virtual void execute(ProgramState* state, std::ostream &outf);
};
#endif //HW2_GOSUB_H
