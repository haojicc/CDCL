//
// Created by Hao Ji on 2023/04/25.
//

#ifndef CDCL_UTIL_H
#define CDCL_UTIL_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class util {
public:
    vector<vector<int>> openFile(string input_filename);
    vector<int> openAns(string input_filename);

    string fmt;
    int num_bvar;
    int num_clause;

    // utility function used to split a clause line and put the reult into a vector
    vector<int> split(const string &s, char delim);

    vector<int> splitAns(const string &s, char delim);

    // untility function to parse the "p cnf $nvar $ncls" line
    void parseHeader(const string &s, char delim, string& fmt, int& num_bvar, int& num_clause);
};



#endif //CDCL_UTIL_H
