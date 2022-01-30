#include "GOSUB.h"

using namespace std;

GOSUB::GOSUB(int line) { line_num = line; }

void GOSUB::execute(ProgramState* state, std::ostream& outf) { state->GOSUB(line_num); }