#include "SubtractStatement.h"

using namespace std;

SubtractStatement::SubtractStatement(string aa, string bb) {
    a = aa;
    b = bb;
}

void SubtractStatement::execute(ProgramState* state, std::ostream& outf) {
    state->subtraction(a, b);
    state->nextline();
}
