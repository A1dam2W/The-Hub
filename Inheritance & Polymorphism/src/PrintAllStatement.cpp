#include "PrintAllStatement.h"

using namespace std;

PrintAllStatement::PrintAllStatement() {}

void PrintAllStatement::execute(ProgramState* state, std::ostream& outf) {
    state->printall();
    state->nextline();
}
