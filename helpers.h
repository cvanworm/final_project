#include <vector>
#include <string>
using namespace std;

#ifndef HELPERS_H
#define HELPERS_H
vector<string> split_string(string str){

    char delimiter = ' ';
    vector<string> result;

    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));

    return result;
}
#endif