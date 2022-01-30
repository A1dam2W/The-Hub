#include "ProgramState.h"

#include <iostream>

using namespace std;

ProgramState::ProgramState(int numLines) {
    m_numLines = 1;
    max_lines = numLines - 1;  // initially pushed back a NULL
    map<string, int> variable;
    stack<int> sta;
}

ProgramState::~ProgramState() {}

void ProgramState::nextline() { m_numLines++; }

int ProgramState::getline() { return m_numLines; }

void ProgramState::Goto(int linenumber) {
    if (linenumber > max_lines) {
        cout << "Illegal jump instruction" << endl;
        endofprogram();
    } else {
        m_numLines = linenumber;
    }
}

bool ProgramState::ifcompare(string var_name, string opr, int val) {
    if (isfound(var_name)) {
        int var_val = getval(var_name);
        if (opr == "=") {
            if (var_val == val) {
                return true;
            } else {
                return false;
            }
        } else if (opr == ">") {
            if (var_val > val) {
                return true;
            } else {
                return false;
            }
        } else if (opr == "<") {
            if (var_val < val) {
                return true;
            } else {
                return false;
            }
        } else if (opr == ">=") {
            if (var_val >= val) {
                return true;
            } else {
                return false;
            }
        } else if (opr == "<=") {
            if (var_val <= val) {
                return true;
            } else {
                return false;
            }
        } else if (opr == "<>") {
            if (var_val != val) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

bool ProgramState::isfound(string s) {
    map<string, int>::iterator it;
    for (it = variable.begin(); it != variable.end(); it++) {
        if (it->first == s) {
            return true;
        }
    }
    return false;
}

void ProgramState::insert(string s, int value) { variable.insert(pair<string, int>(s, value)); }

int ProgramState::getval(string s) {
    map<string, int>::iterator it;
    for (it = variable.begin(); it != variable.end(); it++) {
        if (it->first == s) {
            return it->second;
        }
    }
    return 0;  // default value is zero
}

void ProgramState::setval(string s, int val) {
    map<string, int>::iterator it;
    for (it = variable.begin(); it != variable.end(); it++) {
        if (it->first == s) {
            it->second = val;
        }
    }
}

void ProgramState::GOSUB(int jumpline) {
    sta.push(m_numLines);
    m_numLines = jumpline;
}

int ProgramState::poptop() {
    int t = sta.top();
    sta.pop();
    return t;
}

bool ProgramState::isempty() {
    if (sta.empty()) {
        return true;
    }
    return false;
}

void ProgramState::endofprogram() { m_numLines = 0; }

void ProgramState::printall() {
    map<string, int>::iterator it;
    for (it = variable.begin(); it != variable.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }
}

void ProgramState::addition(string a, string b) {
    map<string, int>::iterator i1 = variable.find(a);
    map<string, int>::iterator i2 = variable.find(b);
    if (i1 != variable.end() and i2 != variable.end()) {
        i1->second += i2->second;
    } else {
        i1->second += stoi(b);
    }
}

void ProgramState::subtraction(string a, string b) {
    map<string, int>::iterator i1 = variable.find(a);
    map<string, int>::iterator i2 = variable.find(b);
    if (i1 != variable.end() and i2 != variable.end()) {
        i1->second -= i2->second;
    } else {
        i1->second -= stoi(b);
    }
}

void ProgramState::multiplication(string a, string b) {
    map<string, int>::iterator i1 = variable.find(a);
    map<string, int>::iterator i2 = variable.find(b);
    if (i1 != variable.end() and i2 != variable.end()) {
        i1->second *= i2->second;
    } else {
        i1->second *= stoi(b);
    }
}

void ProgramState::division(string a, string b) {
    map<string, int>::iterator i1 = variable.find(a);
    map<string, int>::iterator i2 = variable.find(b);
    if (i2->second == 0) {
        endofprogram();
        cout << "Divide by zero exception" << endl;
    }
    if (i1 != variable.end() and i2 != variable.end()) {
        i1->second /= i2->second;
    } else {
        i1->second /= stoi(b);
    }
}
