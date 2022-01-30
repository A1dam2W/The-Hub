#include "dotend.h"

#include <iostream>
using namespace std;

dotend::dotend() {}

void dotend::execute(ProgramState* state, std::ostream& outf) { state->endofprogram(); }