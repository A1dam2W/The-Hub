#include <string>
#include <iostream>
#include <vector>
#include <cmath>

#define protected public
#define private public
#include "Hashtable.h"
#undef protected
#undef private

using namespace std;

int main(){
    //Ruin quadratic probing
    Hashtable<int> hashtable(true, 12);
    hashtable.add("g", 7);
    hashtable.add("j", 10);
    hashtable.add("m", 13);
    hashtable.add("a", 1);
    hashtable.add("d", 4);
    hashtable.reportAll(cout);

    srand(time(0));
    // Probe Rate
    ifstream ifile("rand");
    vector<string> read; string temp;

    for (int i = 0; i < 5000; i++){
        ifile >> temp;
        read.push_back(temp);
    }
    Hashtable<int> num_probe(false,11);
    int count = 0;
    for (int i = 0; i < 5000; i++){
        count += num_probe.add(read[i],count);
    }
    cout << count << endl;
}

