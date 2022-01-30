#include "END.h"

using namespace std;

END::END() {}

void END::execute(ProgramState* state, std::ostream& outf) { state->endofprogram(); }
