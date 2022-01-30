#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

void extended_Euclidean(int e,int L, int& gcd, int& d){
    int t = 1;
    int old_t = 0;
    int r = e;
    int old_r = L;
    while(r!=0){
        int quotient = floor(old_r / r);
        int temp = r;
        r = old_r - quotient * r;
        old_r = temp;
        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }
    gcd = old_r;
    d = old_t;
}

long long modular_exponentiation(long long base, int power, int n){
    long long result = 1;
    base %= n;
    while (power > 0){
        if (power % 2 == 1)
            result = (result * base) % n;
        power = power >> 1;
        base = (base*base) % n;
    }
    return result;
}

int main(int argc, char* argv[]){
    if(argc < 2){
        cout << "Number of input arguments incorrect" << endl;
        return 0;
    }
    int p = stoi(argv[1]);
    int q = stoi(argv[2]);
    int continue_loop = 1;
    while(continue_loop == 1){
        cout << "TYPE ENCRYPT, DECRYPT, or EXIT: ";
        stringstream input; string command, lol;
        vector<int> beforeME;
        int n = p * q;
        if(n < 27){
            cout << "Please choose larger primes" << endl;
            return 0;
        }
        getline(cin,lol);
        input << lol; input >> command;
        if(command == "ENCRYPT"){
            int e = 65537;
            int x = 1 + floor(log(n/27)/log(100));
            string filename, message, encrypted; vector<string> text;
            input >> filename >> n;
            while(input >> message){
                text.push_back(message);
            }
            for(int i = 0;i < text.size();i++){//the for loop which loops through every element of vector
                for(int j = 0;j < text[i].size();j++){//the for loop which loops through every element of the vector at position i
                    if(encrypted.size() == x*2){//size equals 2x indicates that this block has already been converted
                        beforeME.push_back(stoi(encrypted));
                        encrypted="";//reset the string
                    }
                    if(text[i][j]< 106){//converting the character into numbers
                        //'a' is 97, and 'a' should be converted into 01, so we subtract 97 and add 1
                        //which give you subtracting 96
                        //this only handles 01 to 09, so 96+10 = 106
                        encrypted += '0';//adding a leading zero for format issues
                        encrypted += to_string(text[i][j]-96);
                    }
                    else if(text[i][j] == 32){//handling space in message, which has ascii value of 32
                        encrypted += "00";
                    }
                    else{
                        encrypted += to_string(text[i][j]-96);//otherwise this calculation generates the correct result
                    }
                }
                //the above for loop handles all characters, now we should consider adding additional zeros
                if(encrypted.size() == x*2){
                    beforeME.push_back(stoi(encrypted));
                    encrypted = "";
                }
                encrypted += "00";//adding zeros at the end of block with not enough elements to encrypt
            }
            vector<int> out; long long M; int totally_encrypted;
            for(int i = 0;i < beforeME.size();i++){
                M = beforeME[i];
                totally_encrypted = modular_exponentiation(M,e,n);
                out.push_back(totally_encrypted);
            }
            ofstream outfile(filename);
            for(int i = 0;i < out.size();i++){
                outfile << out[i] << " ";//each number in the output file should be separated by a single whitespace
            }
            outfile.close();
        }
        else if(command == "DECRYPT"){
            int e = 65537; int n = p*q; int x = 1 + floor(log(n/27)/log(100));
            string ifile, ofile;
            input >> ifile >> ofile;
            ifstream infile(ifile);
            if (!infile) {
                cout << "Cannot open " << ifile << "!" << endl;
                return 0;
            }
            string message; vector<int> tobedecrypted;
            while(!infile.eof()){
                infile >> message;
                tobedecrypted.push_back(stoi(message));
            }
            if(tobedecrypted[tobedecrypted.size()-1] == tobedecrypted[tobedecrypted.size()-2]){
                tobedecrypted.pop_back();
            }//get rid of the erroneous
            int gcd = 0;
            int extended_gcd = 0;
            int d, rogue_d;
            extended_Euclidean(p-1,q-1,gcd,rogue_d);
            int L = (p-1)*(q-1)/gcd;
            if(L <= e){
                cout << "This L seems a little weird, please try another one" << endl;
                return 0;
            }
            extended_Euclidean(e,L,extended_gcd,d);
            if(d < 0){
                d += (p-1)*(q-1);
            }
            if(extended_gcd != 1){
                cout << "Unfortunate choice of p and q, try other primes" << endl;
                return 0;
            }//item 1 of Decryption process complete
            vector<int> M; int temp; string decrypting;
            for(int i = 0; i < tobedecrypted.size();i++){
                temp = modular_exponentiation(tobedecrypted[i],d,n);
                M.push_back(temp);
            }//calculate M, item 2 completed
            ofstream outfile(ofile); char temp_char; string zeros;
            for(int i = 0;i < M.size();i++){
                decrypting = to_string(M[i]);
                zeros = "";//reset the number of zeros to append, handling white spaces
                if(decrypting.size() < x*2){//stringstream has some pretty interesting reads occasionally
                    for(int j = 0;j < x*2-decrypting.size();j++){
                        zeros += '0';
                    }
                    decrypting = zeros + decrypting;
                }
                for(int counter = 0;counter < decrypting.size();counter+=2){
                    if(decrypting[counter] == '0' and decrypting[counter+1] == '0'){
                        outfile << " ";
                    }// converting "00" into white spaces
                    else if(decrypting[counter] == '0' and decrypting[counter+1] != '0'){
                        int number_at_counter_plus_one = decrypting[counter+1]- 49;//'1' has ascii value of 49
                        temp_char = 'a';
                        temp_char += number_at_counter_plus_one;
                        outfile << temp_char;
                    }
                    else{
                        temp_char = stoi(decrypting.substr(counter,2)) + 96;
                        //I've explained in encryption portion where 96 comes from
                        outfile << temp_char;
                    }
                }
            }
            outfile.close();
        }
        else if(command == "EXIT"){
            continue_loop = 0;
            cout << "Program terminated" << endl;
        }
        else{
            cout << "The program has gracefully terminated." << endl;
        }
    }
}






