#ifndef HW5_HASHTABLE_H
#define HW5_HASHTABLE_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <string>
#include <iostream>
#include <map>

template <class T>
class Hashtable {
public:
    Hashtable(bool debug);
    Hashtable(bool debug, unsigned int size);
    ~Hashtable ();
    int add (std::string k, const T& val);
    const T& lookup (std::string k);
    void reportAll (std::ostream &) const;
private:
    int hash (std::string k) const;
    void resize();
    bool debug_ = false;
    unsigned size; // size of hashtable
    float item; // items in hashtable
    int pos; //corresponding position of the sequence of primes
    std::pair<std::string,T>** ht; //hashtbable to store the string and corresponding value
    std::vector<unsigned int> sequence={11, 23, 47, 97, 197, 397, 797,
                            1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759,
                            411527, 823117};
};

template <class T>
Hashtable<T>::Hashtable(bool debug){
    debug_= debug;
    ht = new std::pair<std::string,T>*[11];
    for(int i = 0;i < 11; i++){
        ht[i] = nullptr;
    }
    size = 11;
    item = 0;
    pos = 0;
}

template <class T>
Hashtable<T>::Hashtable(bool debug, unsigned int size_){
    debug_= debug;
    size = size_;
    ht = new std::pair<std::string,T>*[size];
    for(unsigned int i = 0;i < size; i++){
        ht[i] = nullptr;
    }
    item = 0;
    for(int i = 0; i < 17; i++){//adjust position to the correct space for further calculations
        if(sequence[i] == size_){
            pos = i;
            break;
        }
        else if(sequence[i] > size_){
            pos = i-1;
            break;
        }
    }
}

template <class T>
Hashtable<T>::~Hashtable (){//deleting the hashtable on heap
    for(unsigned int i = 0; i < size; i++) {
        if (ht[i] != nullptr){
            delete ht[i];
        }
    }
    delete[] ht;
}

template <class T>//add string k and corresponding value to the hashtable and return the number of probes
int Hashtable<T>::add (std::string k, const T& val){
    int x = hash(k);
    int A = x;
    int counter = 0;
    for(unsigned i = 0; i < size; i++){
        if(ht[A] == NULL){
            std::pair<std::string,T>* temp=new std::pair<std::string,T>(k,val);
            ht[A] = temp;
            item++;
            break;
        }
        A = x;
        A = (A + i*i) % size;
        counter++;
    }
    if(item/size > 0.35){
        resize();
    }
    return counter;
}

template <class T>
const T& Hashtable<T>::lookup (std::string k){//look up the k's value in the hashtable,
    // and return the first element's value(garbage value) if the item is not found
    int index = hash(k),counter = 1;
    int index_copy = index;
    while(true){
        if(ht[index]->first==k){
            return ht[index]->second;
        }
        else if(ht[index]== nullptr){
            return ht[0]->second;
        }
        else{
            index = index_copy;
            index += pow(counter,2);
            index %= size;
            counter++;
        }
    }
}

/*output everything in hashtable into output file*/
template <class T>
void Hashtable<T>::reportAll (std::ostream & os) const{
    for (unsigned j = 0; j < size; j++){
        if(ht[j] != nullptr){
            os << ht[j]->first << " ";
            os << ht[j]->second << std::endl;
        }
    }
}

//rehashing all the items in the hashtable and increase the table size by approximately 2 times(a larger prime)
template <class T>
void Hashtable<T>::resize(){
    pos++;
    item = 0;
    std::pair<std::string,T>** temp = ht;
    ht = new std::pair<std::string,T>*[sequence[pos]];
    for(unsigned int i = 0; i < sequence[pos]; i++){
        ht[i] = nullptr;
    }
    unsigned size_ = size;
    size = sequence[pos];
    for(unsigned i = 0; i < size_; i++){
        if(temp[i] != nullptr){
                add(temp[i]->first, temp[i]->second);
        }
    }
    delete[] temp;
}

//helper function to calculate 27^5*a1 + 27^4*a2 + 27^3*a3 + 27^2*a4 + 27*a5 + a6
int helper(int len,std::string k){
    long long int w = 0;
    if(len > 6){
        for(int j = 6;j >= 1;j--){
            w += pow(27,j-1)*(k[len-j]-96);
        }
    }
    else if(len <= 6){
        for(int i = 0;i < len;i++){
            w += pow(27,i)*(k[len-1-i]-96);
        }
    }
    return w;
}

/*the hash function that calculate w1 w2 w3 w4 w5 for each value and then calculate (r1 w1 + r2 w2 + r3 w3 + r4 w4 + r5 w5) % m, which is the hash value*/
template <class T>
int Hashtable<T>::hash (std::string k) const{
    int w1 = 0; int w2 = 0; int w3 = 0; int w4 = 0;
    int w5;
    long long int hash_val;
    int len = k.length();
    w5 = helper(len,k);
    len -= 6;
    if(len > 0){
        w4 = helper(len,k);
        len -= 6;
        if(len > 0){
            w3 = helper(len,k);
            len -= 6;
            if(len > 0){
                w2 = helper(len,k);
                len -= 6;
                if(len > 0){
                    w1 = helper(len,k);
                }
            }
        }
    }
    if(debug_){
        long long int r1 = 983132572;
        long long int r2 = 62337998;
        long long int r3 = 552714139;
        long long int r4 = 984953261;
        long long int r5 = 261934300;
        hash_val = (r1*w1 + r2*w2 + r3*w3 + r4*w4 + r5*w5) % size;
    }
    else{
        srand((unsigned)time(NULL));
        long long int r1 = rand()%size;
        long long int r2 = rand()%size;
        long long int r3 = rand()%size;
        long long int r4 = rand()%size;
        long long int r5 = rand()%size;
        hash_val = (r1*w1 + r2*w2 + r3*w3 + r4*w4 + r5*w5) % size;
    }
    return hash_val;
}
#endif //HW5_HASHTABLE_H