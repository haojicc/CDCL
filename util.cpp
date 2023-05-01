//
// Created by Hao Ji on 2023/04/25.
//

#include "util.h"

using namespace std;

vector<int> util::split(const std::string &s, char delim) {
    stringstream ss(s);
    vector<int> items;
    string item;
    while(getline(ss, item, delim)){
        items.push_back(stoi(item));
    }

    return items;

}

vector<int> util::splitAns(const std::string &s, char delim) {
    stringstream ss(s);
    vector<int> items;
    string item;
    while(getline(ss, item, delim)){
        if(item != "v"){
            items.push_back(stoi(item));
        }
    }

    return items;

}

void util::parseHeader(const string &s, char delim, string& fmt, int& num_bvar, int& num_clause){
    stringstream ss(s);
    int count = 0;
    string item;
    while(getline(ss, item, delim)){
        switch(count){
            case 1: fmt = item; break;
            case 2: num_bvar = stoi(item); break;
            case 3: num_clause = stoi(item); break;
        }
        count++;
    }
    return;
}

vector<vector<int>> util::openFile(string input_filename){
    ifstream input_file;
    input_file.open(input_filename);
    vector<vector<int>> res;

    string line;
    vector<int> c;


    if(!input_file.is_open()){
        cout << "ERROR: Failed to open the file" << endl;
        return res;
    }

    while(getline(input_file, line)){
        if(line[0] == 'c'){
            continue;
        } else if(line[0] == 'p'){
            parseHeader(line, ' ', fmt, num_bvar, num_clause);
        } else{
            c = split(line, ' ');
            c.pop_back(); // get rid of the last 0;
            res.push_back(c);
        }
    }

    input_file.close();

    return res;
}


vector<int> util::openAns(string input_filename){
    ifstream input_ans;
    input_ans.open(input_filename);
    vector<int> res;
    res.push_back(0);

    string line;
    vector<int> c;

    if(!input_ans.is_open()){
        cout << "ERROR: Failed to open the file" << endl;
        return res;
    }

    while(getline(input_ans, line)){
        if(line[0] == 's'){
            continue;
        }else if(line[0] == 'v'){
            c = splitAns(line, ' ');
            res.insert(res.end(), c.begin(),c.end());
        }
    }

    input_ans.close();
    return res;
}