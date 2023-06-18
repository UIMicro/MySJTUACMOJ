#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int maxnum = 0;

//stucture for clause
struct clause {
    vector<int> lit;
};

//structure for problem
struct problem {
    vector<clause> par;

    //stat 1: given value true -1: given value false 0: not given value -2: does not exist
    vector<int> stat;
    bool isChanged = true;
}prob;

//if one clause is empty but not deleted, then the SAT is not satisfiable.
bool PendF(problem p) {
    int s = p.par.size();
    for (int i = 0; i < s; i++) {
        if (p.par[i].lit.size() == 0) return true;
    }
    return false;
}
//assign n = true or false, delete true clause and delete element with false value
void Assign(problem* p, int n, bool b) { //assign var and process related clauses.
    p->stat[n] = (b ? 1 : -1);
    for (int i = 0; i < p->par.size(); i++) {
        for (int j = 0; j < p->par[i].lit.size(); j++) {
            if (n == abs(p->par[i].lit[j]) && ((!b && p->par[i].lit[j] < 0) || (b && p->par[i].lit[j] > 0))) {
                p->par.erase(p->par.begin() + i);
                i--;
                break;
            }
            if (n == abs(p->par[i].lit[j]) && ((!b && p->par[i].lit[j] > 0) || (b && p->par[i].lit[j] < 0))) {
                p->par[i].lit.erase(p->par[i].lit.begin() + j);
                j--;
                break;
            }
        }
    }
    return;
}

void UP(problem* p) { //perform unit propagation
    p->isChanged = false;
    for (int i = 1; i < p->par.size(); i++) {
        if (p->par[i].lit.size() == 1) {
            Assign(p, abs(p->par[i].lit[0]), p->par[i].lit[0] > 0);
            p->isChanged = true;
            return;
        }
    }
}

void PLE(problem* p) { //perform pure literal elimination
    p->isChanged = false;
    vector<int> apTime; //How many times does a var appear
    for (int i = 0; i <= maxnum; i++) apTime.push_back(0);
    for (int i = 0; i < p->par.size(); i++) {
        for (int j = 0; j < p->par[i].lit.size(); j++) {
            apTime[abs(p->par[i].lit[j])]++;
        }
    }
    for (int k = 1; k < apTime.size(); k++) {
        if (apTime[k] == 1) {
            for (int i = 0; i < p->par.size(); i++) {
                for (int j = 0; j < p->par[i].lit.size(); j++) {
                    if (abs(p->par[i].lit[j]) == k) {
                        p->par.erase(p->par.begin() + i);
                        i--;
                        p->isChanged = true;
                        break;
                    }
                }
            }
        }
    }
    return;
}


bool DPLL(problem p) {
    p.isChanged = true;
    while (p.isChanged) {
        UP(&p);
    }

    p.isChanged = true;
    while (p.isChanged) {
        PLE(&p);
    }

    if (p.par.size() == 0) return true;
    if (PendF(p)) return false;

    int s = p.stat.size(), n = 0;
    for (int i = 0; i < s; i++) {
        if (p.stat[i] == 0) {
            n = i;
            break;
        }
    }

    //I'm not a master of CPP so I can only write like this... Of course, this can be more optimized.
    problem q, r;
    q.isChanged = p.isChanged;
    q.stat.assign(p.stat.begin(), p.stat.end());
    q.par.assign(p.par.begin(), p.par.end());
    r.isChanged = p.isChanged;
    r.stat.assign(p.stat.begin(), p.stat.end());
    r.par.assign(p.par.begin(), p.par.end());
    //cout << n << endl;
    Assign(&q, n, true);
    Assign(&r, n, false);
    return DPLL(q) || DPLL(r);
}

int main()
{
    bool isS;
    for (int filenum = 0; filenum < 1; filenum++) {
        int linenum, varnum;
        cin >> varnum >> linenum;
        //cout << linenum << " " << varnum << endl;
        for (int l = 0; l < linenum; l++) {
            clause tmpclause;
            int tmp, tmp1;
            for (int v = 0; v < 2; v++) {
                cin >> tmp >> tmp1;
                if (tmp1 == 0) tmp = -tmp;
                tmpclause.lit.push_back(tmp);
                if (abs(tmp) > maxnum) maxnum = abs(tmp);
                //cout << tmp << endl;
            }
            prob.par.push_back(tmpclause);
        }
        for (int i = 0; i <= maxnum; i++) {
            prob.stat.push_back(-2);
        }

        //assign stat of existing vars 0
        for (int i = 0; i < prob.par.size(); i++) {
            for (int j = 0; j < prob.par[i].lit.size(); j++) {
                prob.stat[abs(prob.par[i].lit[j])] = 0;
            }
        }

        //start iter
        isS = DPLL(prob);
        cout << (isS ? "Yes" : "No") << endl;

        //initialize
        prob.par.clear();
        prob.stat.clear();


    }

    return 0;
}
