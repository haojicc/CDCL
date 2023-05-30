#include <iostream>
#include <vector>
#include "util.h"
#include "satSolver.h"
#include <time.h>
#include <stdio.h>

using namespace std;

void test00(){
    string ff = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/add8.cnf";
    string fa = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/sqrt259081.sol";
    time_t start,end;
    time (&start);
    util u;
    auto cnf = u.openFile(ff);
//    auto ans = u.openAns(fa);

    satSolver so(cnf, u.num_clause, u.num_bvar);
//    so.printCNF();

    if(so.solve()){
        cout << "Satisfiable" << endl;
//        so.checkAssignment(ans);
//        so.printAssignment();

    }else{
        cout << "Unsatisfiable" << endl;
//        so.printAssignment();
    }

    cout << "learned clause" << so.getLearnSize() << endl;

    time (&end);
    double dif = difftime (end,start);
    cout << ff << endl;
    printf ("Elasped time is %.2lf seconds.\n", dif );
    return ;
}

void test01(){
    string ff = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/add8.cnf";
    string fa = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/sqrt259081.sol";
    time_t start,end;
    time (&start);
    util u;
    auto cnf = u.openFile(ff);
//    auto ans = u.openAns(fa);

    satSolver so(cnf, u.num_clause, u.num_bvar);
//    so.printCNF();

    if(so.solve()){
        cout << "Satisfiable" << endl;
//        so.checkAssignment(ans);
//        so.printAssignment();

    }else{
        cout << "Unsatisfiable" << endl;
//        so.printAssignment();
    }

    cout << "learned clause" << so.getLearnSize() << endl;

    time (&end);
    double dif = difftime (end,start);
    cout << ff << endl;
    printf ("Elasped time is %.2lf seconds.\n", dif );
    return ;
}

void test02(){
    string ff = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/mytest.cnf";
    string fa = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/sqrt259081.sol";
    time_t start,end;
    time (&start);
    util u;
    auto cnf = u.openFile(ff);
//    auto ans = u.openAns(fa);

    satSolver so(cnf, u.num_clause, u.num_bvar);
//    so.printCNF();

    if(so.solve()){
        cout << "Satisfiable" << endl;
//        so.checkAssignment(ans);
//        so.printAssignment();

    }else{
        cout << "Unsatisfiable" << endl;
//        so.printAssignment();
    }

    cout << "learned clause" << so.getLearnSize() << endl;

    time (&end);
    double dif = difftime (end,start);
    cout << ff << endl;
    printf ("Elasped time is %.2lf seconds.\n", dif );
    return ;
}

void test03(){
    string ff = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/add32.cnf";
    string fa = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/sqrt259081.sol";
    time_t start,end;
    time (&start);
    util u;
    auto cnf = u.openFile(ff);
//    auto ans = u.openAns(fa);

    satSolver so(cnf, u.num_clause, u.num_bvar);
//    so.printCNF();

    if(so.solve()){
        cout << "Satisfiable" << endl;
//        so.checkAssignment(ans);
//        so.printAssignment();

    }else{
        cout << "Unsatisfiable" << endl;
//        so.printAssignment();
    }

    cout << "learned clause" << so.getLearnSize() << endl;

    time (&end);
    double dif = difftime (end,start);
    cout << ff << endl;
    printf ("Elasped time is %.2lf seconds.\n", dif );
    return ;
}

void test04(){
    string ff = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/add64.cnf";
    string fa = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/sqrt259081.sol";
    time_t start,end;
    time (&start);
    util u;
    auto cnf = u.openFile(ff);
//    auto ans = u.openAns(fa);

    satSolver so(cnf, u.num_clause, u.num_bvar);
//    so.printCNF();

    if(so.solve()){
        cout << "Satisfiable" << endl;
//        so.checkAssignment(ans);
//        so.printAssignment();

    }else{
        cout << "Unsatisfiable" << endl;
//        so.printAssignment();
    }

    cout << "learned clause" << so.getLearnSize() << endl;

    time (&end);
    double dif = difftime (end,start);
    cout << ff << endl;
    printf ("Elasped time is %.2lf seconds.\n", dif );
    return ;
}

void test05(){
    string ff = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/ph6.cnf";
    string fa = "/Users/haoji/CLionProjects/CDCL_SAT/cnf/sqrt1042441.sol";
    time_t start,end;
    time (&start);
    util u;
    auto cnf = u.openFile(ff);
    auto ans = u.openAns(fa);

    satSolver so(cnf, u.num_clause, u.num_bvar);
//    so.printCNF();

    if(so.solve()){
        cout << "Satisfiable" << endl;
        so.checkAssignment(ans);
//        so.printAssignment();

    }else{
        cout << "Unsatisfiable" << endl;
//        so.printAssignment();
    }

    cout << "learned clause" << so.getLearnSize() << endl;

    time (&end);
    double dif = difftime (end,start);
    cout << ff << endl;
    printf ("Elasped time is %.2lf seconds.\n", dif );
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
//    test00();
//    test01();
//    test02();
//    test03();
//    test04();
    test05();
    return 0;
}