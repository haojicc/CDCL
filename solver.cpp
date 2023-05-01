//
// Created by Hao Ji on 2023/05/01.
//

#include "solver.h"


solver::solver(vector<vector<int>> &cnf, int numOfClause, int numOfVariable) :cnf(cnf), decisionLevel(0),assignment(numOfVariable+1){
    this->numOfClause = numOfClause;
    this->numOfVariable = numOfVariable;
    initialize();
}

//入口主函数
bool solver::solve() {
    if(!initUnitPropagation()){
        return false;
    }

    decisionLevel++;
    int p = pickVariable();
    while(p != 0){
        trail.push_back(p);
        assignment[abs(p)] = p;
        decisionLevels[p] = decisionLevel;
        reason[p] = -1;

        while(unitPropagation() == false){
            int backtrackLevel = conflictAnalysis();
            if(backtrackLevel < 1){
                return false;
            }else{
                backtrack(backtrackLevel);
            }
        }
        decisionLevel++;
        p = pickVariable();
        if(p == numOfVariable+1){
            return false;
        }

    }

    return true;
}

/*
 * Initialize head/tail lists
 * 把每一个literal取出来，正的放到head里，负的放到tail里。目前我们有三个容器存储cnf相关的信息。
 * cnf：2维数组
 * head：hash-table，里面放了一个1维数组，1维数组里面存了这个变量所在的cnf编码。
 * tail：hash-table，里面放了一个1维数组
 * */
void solver::initialize() {
    cout << "initialize:" << endl;
    for (int i = 0; i < cnf.size(); i++) {
        for (auto var : cnf[i]) {
            if (head.find(var) == head.end()) {
                head[var] = vector<int>();
            }
            head[var].push_back(i); //参数是正数
        }
    }

    assignment = *new vector<int>(numOfVariable+1);
    decisionLevel = 0;
}

/*
 * 需要一个初始化以后检查unit propagation的函数
 * 因为下面的函数是通过在trail里面的literal来进行的。
 * 并且，在这个函数里面，被decision的variables的decision level=0
 * ***在初始化检查unit 的时候，不能只检查一遍，需要把所有的unit 都找出来，比如，一个unit clause隐含着一个确定的literal
 * ***但是这个确定的literal，也可能导致其他的unit propagation
 * ***
 * */
bool solver::initUnitPropagation() {
    queue<int> q;
    for(auto& clause: cnf){
        if(clause.size() > 1){
            continue;
        }
        if(assignment[abs(clause[0])] == -clause[0]){
            return false;
        }
        trail.push_back(clause[0]);
        assignment[abs(clause[0])] = clause[0];
        decisionLevels[clause[0]] = decisionLevel;
        reason[clause[0]] = -1;
        q.push(clause[0]);
    }
    while(!q.empty()){
        int p = q.front();q.pop();
        for (auto clauseId : head[-p]){
            auto& clause = cnf[clauseId];

            int satisfiedLiteral = 0;
            int unassignedLiteral = 0;
            int unassignedNum = 0;

            for (auto literal : clause) {
                int value = assignment[abs(literal)];
                if (value == literal) {
                    satisfiedLiteral++;
                } else if (value == 0) {
                    unassignedLiteral = literal;
                    unassignedNum++;
                }
            }

            if (satisfiedLiteral == 0 && unassignedLiteral == 0) { //发现存在conflict
                return false;
            } else if (satisfiedLiteral == 0 && unassignedNum == 1) { //判断cnf节是否满足unit propagation的条件
                trail.push_back(unassignedLiteral);
                q.push(unassignedLiteral);
                assignment[abs(unassignedLiteral)] = unassignedLiteral;
                decisionLevels[unassignedLiteral] = decisionLevel;
                // 由于是unit propagation所以decision level与决定的是相同的，只有在新的决策的时候，猜会增加。
                // 此时的decisionLevel依旧为0
                reason[unassignedLiteral] = clauseId; //存有向边是因为哪个cnf节，方便后面回溯，也可以方便生成implication graph
            }
        }
    }
    return true;
}

/*
 * 需要把所有已经decision的变量都检查一遍是否有unit 的情况
 * 但是需要一个特定的条件，如果没发现conflict，是要把trail里面的所有元素都pop出来的，这个是为什么呢？
 * */
bool solver::unitPropagation() {
    queue<int> q;
    for(auto it: trail){
        q.push(it);
    }
//    int p = trail.back();
//    q.push(p);
//    cout << "unitPropagation:" << p << endl;

    while(!q.empty()){
        int p = q.front(); q.pop();
        for (auto clauseId : head[-p]) {
            auto& clause = cnf[clauseId];

            int satisfiedLiteral = 0;
            int unassignedLiteral = 0;
            int unassignedNum = 0;

            for (auto literal : clause) { //如何确保这里是unit，
                int value = assignment[abs(literal)];
                if (value == literal) {
                    satisfiedLiteral++;
                } else if (value == 0) {
                    unassignedLiteral = literal;
                    unassignedNum++;
                }
            }

            if (satisfiedLiteral == 0 && unassignedLiteral == 0) { //发现存在conflict
                int conflictLiteral = findConflictLiteral(clause);
                if(conflictLiteral == numOfVariable+1){
                    cout << "Can't Find Conflict Literal!" << endl;
                }
                trail.push_back(conflictLiteral);//如何选择？或者有必要记录是哪个发生了冲突么？
                decisionLevels[conflictLiteral] = decisionLevel;
                reason[conflictLiteral] = clauseId;
                return false;
            } else if (satisfiedLiteral == 0 && unassignedNum == 1) { //判断cnf节是否满足unit propagation的条件
                trail.push_back(unassignedLiteral);
                q.push(unassignedLiteral);
                assignment[abs(unassignedLiteral)] = unassignedLiteral;
                decisionLevels[unassignedLiteral] = decisionLevel; // 由于是unit propagation所以decision level与决定的是相同的，只有在新的决策的时候，猜会增加。
                reason[unassignedLiteral] = clauseId; //存有向边是因为哪个cnf节，方便后面回溯，也可以方便生成implication graph
            }
        }
    }


    return true;
}

/*
 * 从conflict里面学习新的clause
 * 返回一个需要回复的level，然后在函数里面需要调用生成learned clause的函数
 * 返回的level，判断是否为0，如果为0，则unsat，这个判断需要在哪里？
 * */
int solver::conflictAnalysis() {
    vector<int> clause;
    queue<int> q;
    unordered_map<int, bool> seen;
    int rootLevel = 0;
    int p = trail.back();
    q.push(p);
    seen[p] = true;

    while(!q.empty()){
        int currentLiteral = q.front(); q.pop();
        if(reason[currentLiteral] == -1){
            clause.push_back(-assignment[abs(currentLiteral)]);
            rootLevel = max(rootLevel, decisionLevels[currentLiteral]);
            continue;
        }
        seen[currentLiteral] = true;

        for(auto literal: cnf[reason[currentLiteral]]){
            if(seen[literal] == true ){
                continue;
            }
            seen[literal] = true;
            if (reason[-literal] == -1 && decisionLevels[literal] != 0) {
                clause.push_back(-assignment[abs(literal)]);
                rootLevel = max(rootLevel, decisionLevels[-literal]);
            }else{
                q.push(-literal);
            }
        }
    }
    if(clause.size() != 0){
        learnClause(clause);
    }
    return rootLevel;
}

/*
 * 输入是需要回溯到哪一层，清空不必要的数据。
 * */
void solver::backtrack(int level){
    while(!trail.empty()){
        int p = trail.back();
        if(decisionLevels[p] >= level){
            trail.pop_back();
            assignment[abs(p)] = 0;
            searched.erase(p);
            decisionLevels.erase(p);
            reason.erase(p);
        }else{
            decisionLevel = level-1;
            return;
        }
    }
    cout << "backtrack all element of trail!" << endl;
    return;
}

/*
 * 新增的学习clause还需要被记录，这个如何实现？
 * */
void solver::learnClause(vector<int>& clause){
    int newClauseId = cnf.size();
//    cout << "Learn Clause:"<< newClauseId << endl;
//    printClause(clause);
    learned.push_back(newClauseId);
    cnf.push_back(clause);
    for (auto var : clause) {
        head[var].push_back(newClauseId); //参数是正数
    }
    return;
}

int solver::pickVariable() {
    for (int i = 1; i <= numOfVariable; i++) {
        if(assignment[i] != 0){
            continue;
        }
        return i;
    }
    return 0;
}


//辅助函数：
void solver::printCNF(){
    cout << "Print CNF:" << endl;
    for(int i = 0; i < cnf.size(); i++){
        cout << "clause id:  " << i << "\tliterals:   ";
        for(auto var : cnf[i]){
            cout << var << "\t&";
        }
        cout << endl;
    }
}
void solver::printAssignment(){
    cout << "Print Assignment:" << endl;
    for(int i = 1; i<=numOfVariable;i++){
        cout << "variable:  " <<i << "\tvalue:" << assignment[i] << endl;
    }
}
void solver::printHead(){
    cout << "Print Head:" << endl;
    for(int i = 1; i <= numOfVariable; i++){
        auto it = head.find(i);
        auto ite = head.find(-i);
        cout << "variable:  " << it->first << " :" ;
        for(auto clauseId: it->second){
            cout << "\t" << clauseId ;
        }
        cout << endl;
        cout << "variable:  " << ite->first << " :" ;
        for(auto clauseId: ite->second){
            cout << "\t" << clauseId ;
        }
        cout << endl;
    }

//    for(auto it: head){
//        cout << "variable:  " << it.first << " :" ;
//        for(auto clauseId: it.second){
//            cout << "\t" << clauseId ;
//        }
//        cout << endl;
//    }
}
void solver::printTail(){
    cout << "Print Tail:" << endl;
    for(auto it: tail){
        cout << "variable:  " << it.first << " :" ;
        for(auto clauseId: it.second){
            cout << "\t" << clauseId ;
        }
        cout << endl;
    }
}
void solver::printTrail(){
    cout << "Print Trail:" << endl;
    for(int i = 0; i < trail.size(); i++){
        cout << "index:" << i << "   L_t:" << trail[i] << "   R:" << reason[trail[i]] << "   DL:" << decisionLevels[trail[i]] << endl;
    }
}
int solver::findConflictLiteral(vector<int>& clause){
    for(int i = trail.size()-1; i >= 0; i--){
        for(auto literal : clause){
            if(trail[i] == -literal){
                return literal;
            }
        }
    }
    return numOfVariable+1;
}

void solver::printDecisionLevels(){
    cout << "Print Decision Levels:" << endl;
    for(auto it: decisionLevels){
        cout << "variable:  " << it.first << " :"  << it.second << endl;
    }
    cout << "--------------------" << endl;
}

void solver::printReason(){
    cout << "Print Reason:" << endl;
    for(auto it: reason){
        cout << "variable:  " << it.first << " :"  << it.second << endl;
    }
    cout << "--------------------" << endl;
}

void solver::printClause(vector<int>& clause){
    for(auto var: clause){
        cout << var << "\t";
    }
    cout << endl;
}

bool solver::checkAssignment(vector<int>& ans){
    cout << "Check Assignment:" << endl;
    for(int i = 1; i<=numOfVariable;i++){
        if(ans[i] != assignment[i]){
            cout << "No! Something was wr!" << endl;
            return false;
        }
    }
    cout << "OK!" << endl;
    return true;
}

