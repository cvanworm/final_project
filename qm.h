#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

vector<string> remove_duplicates(const vector<string>& vec) {
    unordered_set<string> seen;
    vector<string> unique_vec;

    for (const auto& str : vec) {
        // If the string is not in the set, add it to the output vector and the set
        if (seen.find(str) == seen.end()) {
            unique_vec.push_back(str);
            seen.insert(str);
        }
    }

    return unique_vec;
}

struct implicant{
  string term;
  int used;
};

int get_max_ones(vector<string> terms){
  int max_ones = 0;
  for(int i = 0; i < terms.size(); i++){
    int ones = 0;
    for(int j = 0; j < terms[i].size(); j++){
      if(terms[i][j] == '1') ones++;
    }
    if(ones > max_ones) max_ones = ones;
  }
  return max_ones;
}

vector<vector<implicant>> get_groups(vector<string> term_arr){
  vector<vector<implicant>> groups;
  int max_ones = get_max_ones(term_arr);
  for(int i = 0; i <= max_ones; i++){
    vector<implicant> group;

    for(int j = 0; j < term_arr.size(); j++){
      int ones = 0;
      for(int k = 0; k < term_arr[j].size(); k++){
        if(term_arr[j][k] == '1') ones++;
      }
      if(ones == i){
        implicant term = {term_arr[j], 0};
        group.push_back(term);
      }
    }
    if(group.size() > 0) groups.push_back(group);
  }
  return groups;
}

int one_bit_diff(string a, string b){
  int index = 0;
  int diff = 0;
  bool one_bit_diff = false;
  for(int i = 0; i < a.size(); i++){
    if(a[i] != b[i]){
      diff++;
      if(diff == 1){
        index = i;
      }else{
        index = -1;
      }  
    }
  }
  return index;
}

vector<string> find_prime_implicants(vector<string> minterms, vector<string> dontcares){
  vector<string> all_terms;
  all_terms.insert(all_terms.end(), minterms.begin(), minterms.end());
  all_terms.insert(all_terms.end(), dontcares.begin(), dontcares.end());

  vector<vector<implicant>> groups = get_groups(all_terms);
  vector<string> prime_implicants;
  all_terms.clear();

  while(true){
    for(int i=0; i<groups.size()-1; i++){
        for(int j=0; j<groups[i].size(); j++){
          for(int k=0; k<groups[i+1].size(); k++){
            int index = one_bit_diff(groups[i][j].term, groups[i+1][k].term);
            if(index != -1){
              groups[i][j].used = 1;
              groups[i+1][k].used = 1;
              string tmp = groups[i][j].term;
              tmp[index] = '-';
              int cnt = count(all_terms.begin(), all_terms.end(), tmp);
              if(cnt==0){
                all_terms.push_back(tmp);
              } 
            }
          }
          if(groups[i][j].used == 0){
            prime_implicants.push_back(groups[i][j].term);
          }
        }
      }
      
      for(int i=0; i<groups[groups.size()-1].size(); i++){
        if(groups[groups.size()-1][i].used == 0){
          prime_implicants.push_back(groups[groups.size()-1][i].term);
        }
      }

      if(all_terms.size() == 0){
        break;
      }else{
        groups = get_groups(all_terms);
        all_terms.clear();
      }

  }

  return prime_implicants;
  
}

// Function to check if a prime implicant (with '-') covers a minterm
bool covers(const string& primeImplicant, const string& minterm) {
    for (size_t i = 0; i < primeImplicant.size(); i++) {
        if (primeImplicant[i] != '-' && primeImplicant[i] != minterm[i]) {
            return false;
        }
    }
    return true;
}

// Step 1: Generate the Prime Implicant Table
vector<vector<bool>> generatePrimeImplicantTable(const vector<string>& minterms, const vector<string>& primeImplicants) {
    vector<vector<bool>> table(primeImplicants.size(), vector<bool>(minterms.size(), false));
    
    for (size_t i = 0; i < primeImplicants.size(); i++) {
        for (size_t j = 0; j < minterms.size(); j++) {
            table[i][j] = covers(primeImplicants[i], minterms[j]);
        }
    }
    return table;
}

// Step 2: Find Essential Prime Implicants
vector<string> findEssentialPrimeImplicants(const vector<vector<bool>>& table, const vector<string>& primeImplicants, const vector<string>& minterms) {
    vector<string> essentialPrimeImplicants;
    vector<bool> coveredMinterms(minterms.size(), false);
    
    // Check each minterm
    for (size_t j = 0; j < minterms.size(); j++) {
        int count = 0;
        int essentialIdx = -1;

        // Count how many prime implicants cover this minterm
        for (size_t i = 0; i < primeImplicants.size(); i++) {
            if (table[i][j]) {
                count++;
                essentialIdx = i;
            }
        }

        // If only one prime implicant covers this minterm, it is essential
        if (count == 1) {
            essentialPrimeImplicants.push_back(primeImplicants[essentialIdx]);

            // Mark all minterms covered by this essential prime implicant
            for (size_t k = 0; k < minterms.size(); k++) {
                if (table[essentialIdx][k]) {
                    coveredMinterms[k] = true;
                }
            }
        }
    }

    // Add remaining prime implicants to cover uncovered minterms
    for (size_t j = 0; j < minterms.size(); j++) {
        if (!coveredMinterms[j]) {
            for (size_t i = 0; i < primeImplicants.size(); i++) {
                if (table[i][j] && find(essentialPrimeImplicants.begin(), essentialPrimeImplicants.end(), primeImplicants[i]) == essentialPrimeImplicants.end()) {
                    essentialPrimeImplicants.push_back(primeImplicants[i]);

                    // Mark covered minterms
                    for (size_t k = 0; k < minterms.size(); k++) {
                        if (table[i][k]) {
                            coveredMinterms[k] = true;
                        }
                    }
                    break;
                }
            }
        }
    }

    return essentialPrimeImplicants;
}
