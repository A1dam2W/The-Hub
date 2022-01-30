#include "RETURN.h"

using namespace std;

RETURN::RETURN() {}

void RETURN::execute(ProgramState* state, std::ostream& outf) {
    if (state->isempty()) {
        state->endofprogram();
    } else {
        line_num = state->poptop() + 1;
        state->Goto(line_num);
    }
}
