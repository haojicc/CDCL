//
// Created by Hao Ji on 2023/05/01.
//

#ifndef CDCL_SOLVER_H
#define CDCL_SOLVER_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include "unordered_set"
#include "queue"
using namespace std;

class solver {
public:
    solver(vector<vector<int>>& cnf, int numOfClause, int numOfVariable);
    bool solve();
    void initialize();
    bool initUnitPropagation();
    bool unitPropagation();
    int conflictAnalysis();
    void backtrack(int level);
    void learnClause(vector<int>& clause);
    int pickVariable();

    //辅助函数
    void printCNF();
    void printAssignment();
    void printHead();
    void printTail();
    void printTrail();
    void printDecisionLevels();
    void printReason();
    void printClause(vector<int>& clause);
    bool checkAssignment(vector<int>& ans);

private:
    vector<int> assignment; //直接存正负值，不用1和-1来表示，如果是0，代表还没有分配
    vector<vector<int>> cnf; //每个数组都是一个cnf节，变量的表示用正负整数
    unordered_map<int, vector<int>> head;
    unordered_map<int, vector<int>> tail;
    unordered_map<int, int> reason; // 只会记录最后决定的那个clause，-1为decison或者是单位clause中的一个variable
    vector<int> trail;//记录decision variable
    unordered_map<int, int> decisionLevels;//记录variable是在哪一层被决策的，记录的是绝对值
    int decisionLevel;
    vector<int> learned;//记录被学习的clause的id
    unordered_set<int> searched;//记录已经被探索过的branch   这个需要在每次pick的时候也要记录，回溯的时候记录需要删除，只保留回溯decision level以上的值
    int numOfClause;
    int numOfVariable;

    //辅助函数
    int findConflictLiteral(vector<int>& clause);
};


#endif //CDCL_SOLVER_H
