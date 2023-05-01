#include <iostream>
#include <vector>
#include "util.h"
#include "solver.h"

using namespace std;


void test01(){
    string ff = "/Users/haoji/CLionProjects/CDCL/cnf/add8.cnf";
    string fa = "/Users/haoji/CLionProjects/CDCL/cnf/prime529.sol";
    util u;
    auto cnf = u.openFile(ff);
//    auto ans = u.openAns(fa);

    solver so(cnf,u.num_clause,u.num_bvar);
//    so.printCNF();
//    so.printHead();

    if(so.solve()){
        cout << "Satisfiable" << endl;
//        so.checkAssignment(ans);
        so.printAssignment();

    }else{
        cout << "Unsatisfiable" << endl;
        so.printAssignment();
    }

    return ;
}







int main() {
//    vector<vector<int>> cnf = {
//            {1,  2, 3},
//            {-1, -2},
//            {-2, -3},
//            {-1, 3},
//            {1,  -3},
//    };
    test01();
    return 0;
}