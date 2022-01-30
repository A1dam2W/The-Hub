#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void swap(char* a, char* b) {
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void helper(std::string str, int front, int back) {
    for (int i = front; i <= back; i++) {
        for (int j = i + 1; j <= back; j++) {
            swap(str[i], str[j]);
            cout << str << endl;
            helper(str, i + 1, back);
            swap(str[i], str[j]);
        }
    }
}

void permutations(std::string in) {
    helper(in, 0, in.length() - 1);
    cout << in << endl;
}
