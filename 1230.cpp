#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>

/*
*   MicroCDCL SAT SOLVER by:
*	 --	 ---  |\  |  /--- \   / |   |  ---  |\  |   --/ |   | /---\ |   |
*	|-- | - | | \ | |  __  \ /  |   | | - | | \ |    /  |---| |   | |   |
*	|	|   | |  \|  \__/   |   \___/ |   | |  \|   /-- |   | \___/ \___/
*/

using namespace std;

class Clause {
public:
	vector<int> literal;

};

class Variable {
public:
	Variable();
	enum Value {
		F, T, u //False, True, Unassigned
	};
	Value value;
	Clause antecedent;
	int level;
};

class DecisionLevel {
public:
	DecisionLevel(int VarNum, int cnum);
	vector<Clause> clause;
	vector<Variable> variable;
	vector<int> DecideTree;
	int level;
	void RemoveRepeat();
	bool UP();
	bool AllAssigned();
	bool Conflict();
	Clause Learn(int& BackLayer);
	void PickAndAssign();
private:
	Clause ConflictClause;
};

class CNF {
public:
	CNF();
	vector<DecisionLevel> level;
	bool solve();
	int curlevel;
private:
	int VarNum;
	int ClauseNum;
};


//Solve the problem
bool CNF::solve() {
	while (1) {

		//First, try to do unit propagation
		while (this->level.at(this->curlevel).UP());

		//Determine conflict
		if (level.at(curlevel).Conflict()) {

			//Unsatisfiable case
			if (curlevel == 0) {
				return false;
			}

			//Try to learn a new clause from conflict
			int back;
			Clause c = this->level.at(this->curlevel).Learn(back);
			this->curlevel = back;
			while (level.size() > back + 1) level.pop_back();

			//Add learned clause to the clause array
			//(level.end() - 1)->clause.push_back(c);
			for (auto i = level.begin(); i != level.end(); ++i) {
				i->clause.push_back(c);
			}
		}
		else {
			//Satisfied case
			if (this->level.at(this->curlevel).AllAssigned()) {
				return true;
			}
			else {
				//Pick a variable and assign a value
				this->level.push_back(this->level.at(curlevel));
				++curlevel;
				level.at(curlevel).level++;
				level.at(curlevel).PickAndAssign();
			}
		}
	}
}

//find an unassigned variable and assign true
void DecisionLevel::PickAndAssign() {
	//If conflict occurs when assigned true, a clause would be learned and would assign it false in the following UP.
	for (auto i = this->variable.begin() + 1; i != this->variable.end(); ++i) {
		if (i->value == Variable::u) {
			i->value = Variable::T;
			i->level = level;
			this->DecideTree.push_back(distance(this->variable.begin(), i));
			//cout << "Assigned:" << distance(this->variable.begin(), i) << '=' << (i->value == Variable::T ? "T" : "F") << endl;
			return;
		}
	}
}
void printclause(Clause c) {
	cout << "Learned Clause: ";
	for (auto i = c.literal.begin(); i != c.literal.end(); ++i) {
		cout << *i << ' ';
	}
	cout << endl;
}

//Learn a clause to avoid conflict next time
Clause DecisionLevel::Learn(int& BackLayer) {
	//A basic method of learning clauses is to use a queue.
	//This can be improved by considering UIP, meanwhile dramatically increases code difficulty. I'll try if I have time.
	vector<int> fashion;
	set<int> rec;
	bool hasdec = false;
	//First process the conflict node
	for (auto i = ConflictClause.literal.begin(); i != ConflictClause.literal.end(); ++i) {
		if (variable.at(abs(*i)).level < level) {
			rec.insert(*i);
		}
		else {
			fashion.push_back(*i);
			if (abs(DecideTree.back()) == abs(*i)) {
				hasdec = true;
			}
		}
	}

	//Iterate while the queue is not empty.
	while (fashion.size() != 0) {

		int ext = fashion.front();
		if (abs(ext) == abs(DecideTree.back())) hasdec = false;
		int curlevcnt = 0, uipnum;
		for (auto i = fashion.begin(); i != fashion.end(); ++i) {
			if (level == variable.at(abs(*i)).level) {
				curlevcnt++;
				uipnum = *i;
			}
		}
		if (curlevcnt == 1) {
			rec.insert(uipnum);
			break;
		}
		fashion.erase(fashion.begin());
		if (abs(ext) == abs(DecideTree.back()) && !hasdec) {
			fashion.push_back(ext);
			hasdec = true;
			continue;
		}
		for (auto i = variable.at(abs(ext)).antecedent.literal.begin(); i != variable.at(abs(ext)).antecedent.literal.end(); ++i) {
			if (abs(*i) != abs(ext)) {
				if (variable.at(abs(*i)).level < level) {
					rec.insert(*i);
				}
				else {
					if (abs(DecideTree.back()) == abs(*i)) {
						if (!hasdec) {
							fashion.push_back(*i);
							hasdec = true;
						}
					}
					else {
						fashion.push_back(*i);
					}
				}
			}
		}
	}
	Clause c;
	vector<int> lay;

	//Construct a clause
	while (!rec.empty()) {
		int i = *rec.begin();
		c.literal.push_back(i);
		rec.erase(rec.begin());
	}

	//Try to find the second largest decision level of the learned clause and traceback to that.
	for (auto i = c.literal.begin(); i != c.literal.end(); ++i) {
		lay.push_back(variable.at(abs(*i)).level);
	}
	if (lay.size() == 1) BackLayer = level - 1;
	else {
		int max = -1, secmax = -1;
		for (auto i = lay.begin(); i != lay.end(); ++i) {
			if (max < *i) max = *i;
		}
		for (auto i = lay.begin(); i != lay.end(); ++i) {
			if ((*i != max) && (secmax < *i)) secmax = *i;
		}
		if (secmax == -1) BackLayer = level - 1;
		else BackLayer = secmax;
	}
	//printclause(c);
	//cout << "Back to layer " << BackLayer << endl;
	return c;
}

//Remove Repeat Literals. This is essensial for some cases.
void DecisionLevel::RemoveRepeat() {
	for (auto i = clause.begin(); i != clause.end(); ++i) {
		set<int> lttmp;
		for (auto j = i->literal.begin(); j != i->literal.end(); ++j) {
			lttmp.insert(*j);
		}
		i->literal.clear();
		while (!lttmp.empty()) {
			i->literal.push_back(*lttmp.begin());
			lttmp.erase(lttmp.begin());
		}
	}
}

//Unit Propagation
bool DecisionLevel::UP() {
	int assF, unass;
	bool found = false;
	vector<Clause>::iterator cls;

	//Find a unit clause. If cannot find, return false.
	for (auto i = this->clause.begin(); i != this->clause.end(); ++i) {
		assF = 0;
		unass = 0;
		for (auto j = i->literal.begin(); j != i->literal.end(); ++j) {
			if ((this->variable.at(abs(*j)).value == Variable::T) && (*j < 0)
				|| (this->variable.at(abs(*j)).value == Variable::F) && (*j > 0)) {
				assF++;
			}
			if (this->variable.at(abs(*j)).value == Variable::u) {
				unass++;
				if (unass > 1) break;
			}
		}
		if (assF == i->literal.size() - 1 && unass == 1) {
			found = true;
			cls = i;
			break;
		}
	}
	if (!found) return false;

	//Find and assign the variable.
	int ulit;
	for (auto i = cls->literal.begin(); i != cls->literal.end(); ++i) {
		if (this->variable.at(abs(*i)).value == Variable::u) {
			ulit = *i;
			break;
		}
	}
	this->variable.at(abs(ulit)).value = ((ulit > 0) ? Variable::T : Variable::F);
	this->variable.at(abs(ulit)).antecedent = *cls;
	this->variable.at(abs(ulit)).level = level;
	//cout << "UP Assigned:" << abs(ulit) << '=' << (variable.at(abs(ulit)).value == Variable::T ? "T" : "F") << endl;

	//remove clauses with a definite value
	bool flag = false;
	for (auto i = this->clause.begin(); i != clause.end(); i += (int)(!flag)) {
		flag = false;
		for (auto j = i->literal.begin(); j != i->literal.end(); ++j) {
			if (abs(*j) == abs(ulit)) {
				if (ulit * *j > 0) {
					flag = true;
					i = clause.erase(i);
					break;
				}
			}
		}
	}
	return true;
}

//Check if all variables are assigned
bool DecisionLevel::AllAssigned() {
	for (auto i = this->variable.begin() + 1; i != this->variable.end(); i++) {
		if (i->value == Variable::u) return false;
	}
	return true;
}

//Check if there is a conflict for current assignment
bool DecisionLevel::Conflict() {
	for (auto i = this->clause.begin(); i != this->clause.end(); ++i) {
		bool tr = false;
		for (auto j = i->literal.begin(); j != i->literal.end(); ++j) {
			if (this->variable.at(abs(*j)).value == Variable::u || (this->variable.at(abs(*j)).value == Variable::T) && (*j > 0) || (this->variable.at(abs(*j)).value == Variable::F) && (*j < 0)) {
				tr = true;
				break;
			}
		}
		if (!tr) {
			ConflictClause = *i;
			return true;
		}
	}
	return false;
}

//Initialize a variable
Variable::Variable() {
	value = u;
	level = -1;
}

//Initialize a decisionlevel
DecisionLevel::DecisionLevel(int vnum, int cnum) {
	for (int i = 0; i <= vnum; i++) {
		variable.push_back(Variable());
	}
	level = 0;
}

//Initialize the problem
CNF::CNF() {
	curlevel = 0;
	int varnum, rulenum;
	cin >> varnum >> rulenum;
	vector<Clause> ctmp;
	for (int i = 0; i < rulenum; i++) {
		Clause c;
		int temp1, temp2;
		cin >> temp1 >> temp2;
		if (temp2) {
			c.literal.push_back(temp1);
		}
		else {
			c.literal.push_back(-temp1);
		}
		cin >> temp1 >> temp2;
		if (temp2) {
			c.literal.push_back(temp1);
		}
		else {
			c.literal.push_back(-temp1);
		}
		ctmp.push_back(c);
	}
	VarNum = varnum;
	DecisionLevel d(VarNum, ClauseNum);
	d.clause = ctmp;
	d.RemoveRepeat();
	d.level = 0;
	level.push_back(d);
}

int main()
{
	CNF p;
	if (p.solve()) {
		cout << "Yes";
	}
	else {
		cout << "No";
	}
	return 0;
}
