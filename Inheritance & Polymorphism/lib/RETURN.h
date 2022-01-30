#ifndef HW2_RETURN_H
#define HW2_RETURN_H

#include "Statement.h"

class RETURN:public Statement{
private:
    int line_num;
public:
    RETURN();
    virtual void execute(ProgramState* state, std::ostream &outf);
};

#endif //HW2_RETURN_H
