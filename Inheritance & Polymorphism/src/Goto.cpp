#include "Goto.h"

#include <iostream>

Goto::Goto(int a) { line_num = a; }

void Goto::execute(ProgramState* state, ostream& outf) { state->Goto(line_num); }
