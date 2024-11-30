#include "qm.h"
#include "pla_functions.h"

int main(int argc, char* argv[]){
    
    PLA input_pla = read_input(argv[1]);

    vector<string> prime_implicants = find_prime_implicants(input_pla.minterms, input_pla.dontcares);
    // printf("Prime Implicants:");
    // for(int i=0; i<prime_implicants.size()-1; i++){
    //     printf("%s, ", prime_implicants[i].c_str());
    // }
    // printf("%s\n\n", prime_implicants[prime_implicants.size()-1].c_str());
    
    vector<vector<bool>> table = generatePrimeImplicantTable(input_pla.minterms, prime_implicants);
    vector<string> solution = findEssentialPrimeImplicants(table, prime_implicants, input_pla.minterms);

    write_pla(solution, input_pla.input_labels);
    return 0;
}


