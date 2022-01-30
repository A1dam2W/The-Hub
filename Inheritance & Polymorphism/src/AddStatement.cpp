#include "AddStatement.h"

using namespace std;

AddStatement::AddStatement(string aa, string bb) {
    a = aa;
    b = bb;
}

void AddStatement::execute(ProgramState* state, std::ostream& outf) {
    state->addition(a, b);
    state->nextline();
}
