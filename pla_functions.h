#include "helpers.h"
#include <fstream>

using namespace std;

#ifndef READ_INPUT_H
#define READ_INPUT_H

struct PLA{
    int num_inputs;
    int num_outputs;
    int num_minterms;
    char output_labels;
    vector<string> input_labels;
    vector<string> minterms;
    vector<string> dontcares;
};

PLA read_input(string filename){
    PLA pla;

    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while(getline(file, line)){
            vector<string> tokens = split_string(line);
            if(tokens[0] == ".i"){
                pla.num_inputs = stoi(tokens[1]);
            }else if(tokens[0] == ".o"){
                pla.num_outputs = stoi(tokens[1]);
            }else if(tokens[0] == ".ilb"){
                for(int i=1; i<tokens.size(); i++){
                    pla.input_labels.push_back(tokens[i]);
                }
            }else if(tokens[0] == ".ob"){
                pla.output_labels = tokens[1][0];
            }else if(tokens[0] == ".p"){
                pla.num_minterms = stoi(tokens[1]);
            }else if(tokens[0] == ".e"){
                break;
            }else{
                
                if(tokens[1] == "-"){
                    pla.dontcares.push_back(tokens[0]);
                }else{
                    pla.minterms.push_back(tokens[0]);
                }
            }
        }
    }
    file.close();
    return pla;
}

void write_pla(vector<string> solution, vector<string> labels){
    ofstream file("solution.pla");
    int num_inputs = solution[0].size();
    int num_outputs = 1;
    int num_minterms = solution.size();
    if(file.is_open()){
        file << ".i " << num_inputs << "\n";
        file << ".o 1\n";
        file << ".ilb ";
        for(int i=0; i<labels.size(); i++){
            file << labels[i] << " ";
        }
        file << "\n";
        file << ".ob Z\n";
        file << ".p " << num_minterms << "\n";
        for(int i=0; i<solution.size(); i++){
            file << solution[i] << " 1\n";
        }
        file << ".e\n";
        
    }
    file.close();
}

#endif