#include <algorithm>
#include <string>
#include "MinHeap.h"
#include <fstream>
#include <map>

using namespace std;

struct node{
    string word;
    node* parent;
    int g, h, f, priority;
    node(string s, node* predecessor, int distance){
        word = s; parent = predecessor; g = distance;
    }
};//heuristic calculation comes afterwards in setup_node because we'll have to compare with the finish node
void setup_node(node* curr, node* goal){
    curr->h = curr->word.size();
    for(int i = 0; i < curr->word.size(); i++){
        if (curr->word[i] == goal->word[i]){
            curr->h--;
        }
    }
    curr->priority = (curr->h+curr->g)*(curr->word.size()+1) + curr->h;
    curr->f = curr->h + curr->g;
}

int trace_back(node* a){
    int steps = 0;
    while (a != nullptr) {
        a = a->parent;
        steps++;
    }
    return steps-1;
}

int main(int argc, char* argv[]){
    if(argc < 3){
        cout << "Number of input arguments incorrect" << endl;
        return 0;
    }
    map<string, int> dictionary;
    node *start = new node(argv[1], nullptr, 0);
    dictionary[start->word] = 1;
    node *finish = new node(argv[2], nullptr,0);
    setup_node(start, finish);
    setup_node(finish, finish);
    MinHeap<node*> *openset = new MinHeap<node *>(2);
    openset->add(start, start->priority);
    int total;
    string word_from_file;
    ifstream ifile(argv[3]);
    if(!ifile.is_open()){
        throw "Exception: File name error.";
    }
    else{
        ifile >> total;
        while(ifile >> word_from_file){
            transform(word_from_file.begin(), word_from_file.end(), word_from_file.begin(), ::tolower);
            if (word_from_file.size() == start->word.size()) {
                dictionary[word_from_file] = 0;
            }
        }
    }
    int expansion = 0;
    while(!openset->isEmpty()){
        node* temp = openset->peek();
        openset->remove();
        if(temp->word == finish->word){
            int total_steps = trace_back(temp);
            cout << total_steps << endl;
            cout << expansion;
            return 0;
        }
        for(int i = 0; i < temp->word.size(); i++){
            for(int j = 0; j < 26; j++){
                string temp_word = temp->word;
                temp_word[i] = 97 + j;
                if(temp->word == temp_word){
                    continue;
                }
                if(dictionary.count(temp_word) > 0 and dictionary[temp_word] == 0){
                    node *expand = new node(temp_word, temp, temp->g + 1);
                    setup_node(expand, finish);
                    openset->add(expand, expand->priority);
                    dictionary[temp_word] = 1;
                }
                else if(dictionary.count(temp_word) > 0 and dictionary[temp_word] == 1){
                    node* temp2 = new node(temp_word, temp, temp->g + 1);
                    setup_node(temp2, finish);
                    for(int k = 0; k < openset->size; k++){
                        if(openset->item_at_pos(k)->word == temp_word){
                            if(temp2->priority < openset->priority_at_pos(k)){
                                openset->add(temp2, temp2->priority);
                                openset->remove(k);
                            }
                        }
                    }
                }
            }
        }
        dictionary[temp->word] = -1;
        expansion++;
    }
    cout << "No transformation" << endl;
    cout << expansion;
    return 0;
}





