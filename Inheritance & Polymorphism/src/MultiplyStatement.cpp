#include "MultiplyStatement.h"

using namespace std;

MultiplyStatement::MultiplyStatement(string aa, string bb) {
    a = aa;
    b = bb;
}

void MultiplyStatement::execute(ProgramState* state, std::ostream& outf) {
    state->multiplication(a, b);
    state->nextline();
}
