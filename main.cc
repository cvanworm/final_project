#include "qm.h"


int main(int argc, char* argv[]){

    vector<string> minterms = {"0010", "0011", "1001", "0111", "1011", "1101"};
    vector<string> dontcares = {"0001", "1010", "1111"};

    vector<string> prime_implicants = find_prime_implicants(minterms, dontcares);
    printf("Prime Implicants:");
    for(int i=0; i<prime_implicants.size()-1; i++){
        printf("%s, ", prime_implicants[i].c_str());
    }
    printf("%s\n\n", prime_implicants[prime_implicants.size()-1].c_str());
    
    vector<vector<bool>> table = generatePrimeImplicantTable(minterms, prime_implicants);
    vector<string> solution = findEssentialPrimeImplicants(table, prime_implicants, minterms);

    printf("Solution: f = ");
    for(int i=0; i<solution.size(); i++){
        if(i == solution.size()-1){
            printf("%s\n", solution[i].c_str());
        }else{
            printf("%s + ", solution[i].c_str());
        }
    }

    return 0;
}


