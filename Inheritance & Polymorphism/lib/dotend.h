#ifndef HW2_DOTEND_H
#define HW2_DOTEND_H

#include "Statement.h"
class dotend : public Statement{

public:
    dotend();
    virtual void execute(ProgramState* state, std::ostream &outf);
};

#endif //HW2_DOTEND_H
