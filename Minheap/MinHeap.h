#ifndef HW3_MINHEAP_H
#define HW3_MINHEAP_H
#include <iostream>
#include <stdexcept>
#include <vector>

template<class T>
class MinHeap{
public:
    MinHeap(int d);
    ~MinHeap();
    void add(T item,int priority);
    const T & peek() const;
    void remove();
    void remove(int pos);
    bool isEmpty();
    void bubble_up(int pos);
    void trickle_down(int pos);
    const T & item_at_pos(int pos);
    int priority_at_pos(int pos);
    int size;
    int whatheap;
    std::vector<T> dnaryheap;
    std::vector<int> prior;
};

template<typename T>
MinHeap<T>::MinHeap(int d){
    size = 0;
    whatheap = d;
}

template<typename T>
MinHeap<T>::~MinHeap(){}

template<typename T>
void MinHeap<T>::add(T item,int priority){
    dnaryheap.push_back(item);
    prior.push_back(priority);
    size++;
    bubble_up(dnaryheap.size()-1);
}

template<typename T>
void MinHeap<T>::remove(){
    if(size == 0){
        throw "Empty heap";
    }
    std::swap(dnaryheap[0],dnaryheap[dnaryheap.size()-1]);
    std::swap(prior[0],prior[dnaryheap.size()-1]);
    size--;
    dnaryheap.pop_back();
    prior.pop_back();
    trickle_down(0);
}

template<typename T>
void MinHeap<T>::remove(int pos){
    if (size == 0){
        throw "Empty heap";
    }
    std::swap(dnaryheap[pos],dnaryheap[dnaryheap.size()-1]);
    std::swap(prior[pos],prior[dnaryheap.size()-1]);
    size--;
    dnaryheap.pop_back();
    prior.pop_back();
    trickle_down(pos);
}

template<typename T>
const T& MinHeap<T>::peek() const{
    if (dnaryheap.size() == 0){
        throw "Empty heap";
    }
    return dnaryheap[0];
}

template<typename T>
const T & MinHeap<T>::item_at_pos(int pos){
    return dnaryheap[pos];
}

template<typename T>
int MinHeap<T>::priority_at_pos(int pos){
    return prior[pos];
}

template <class T>
bool MinHeap<T>::isEmpty (){
    if(dnaryheap.size() == 0){
        return true;
    }
    return false;
}

template<typename T>
void MinHeap<T>::bubble_up(int pos){
    if(pos > 0 and prior[pos] < prior[(pos-1)/whatheap]){
        std::swap(dnaryheap[pos],dnaryheap[(pos-1)/whatheap]);
        std::swap(prior[pos],prior[(pos-1)/whatheap]);
        bubble_up((pos-1)/whatheap);
    }
    else if(pos > 0 and prior[pos] == prior[pos-1]){
        while(dnaryheap[pos] < dnaryheap[pos-1]){
            std::swap(dnaryheap[pos],dnaryheap[pos-1]);
            std::swap(prior[pos],prior[pos-1]);
            bubble_up(pos-1);
        }
    }
}

template<typename T>
void MinHeap<T>::trickle_down(int pos){
    int child = whatheap * pos +1;
    if(child >= dnaryheap.size()){
        return;
    }
    int temp_pos = child;
    for (int i =1; i < whatheap; i++){
        if (child+i < dnaryheap.size() and prior[child+i] < prior[temp_pos]){
            temp_pos = child+i;
        }
    }//the for loop that go through all the children with given different priorities
    child = temp_pos;
    if(prior[pos] > prior[child]){
        std::swap(dnaryheap[pos],dnaryheap[child]);
        std::swap(prior[pos],prior[child]);
        trickle_down(child);
    }
    else if(pos >= 0 and prior[pos] == prior[child]){
        if(dnaryheap[pos] > dnaryheap[child]){
            std::swap(dnaryheap[pos],dnaryheap[child]);
            std::swap(prior[pos],prior[child]);
            trickle_down(child);
        }
    }
}
#endif //HW3_MINHEAP_H
