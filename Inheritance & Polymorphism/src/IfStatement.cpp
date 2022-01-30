#include "IfStatement.h"

#include <iostream>

IfStatement::IfStatement(string var_nam, string op, int va, int lin) {
    var_name = var_nam;
    opr = op;
    val = va;
    line = lin;
}

void IfStatement::execute(ProgramState* state, std::ostream& outf) {
    if (state->ifcompare(var_name, opr, val)) {
        state->Goto(line);
    } else {
        state->nextline();
    }
}