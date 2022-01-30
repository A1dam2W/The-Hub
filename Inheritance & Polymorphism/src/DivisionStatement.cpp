#include "DivisionStatement.h"

using namespace std;

DivisionStatement::DivisionStatement(string aa, string bb) {
    a = aa;
    b = bb;
}

void DivisionStatement::execute(ProgramState* state, std::ostream& outf) {
    state->division(a, b);
    state->nextline();
}
