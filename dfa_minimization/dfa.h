#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class dfa {
public:
	vector<vector<int>> input;
	unordered_map<int, int> GroupNumber;
	vector<vector<vector<int>>> Groups;
	unordered_map<int, string> stateConcatenation;
	int newGroup = 2;
	bool flag = true;

	dfa(int states) {
		input.resize(states);
		Groups.resize(states);
		for (int i = 0; i < states; ++i) {
			GroupNumber[i] = 1;
		}
	}

	void takeinput() {
		int states;
		cout << "Enter number of states:";
		cin >> states;
		for (int i = 0; i < states; i++) {
			int t1, t2;
			char ch;
			cout << "For state q" << i << " and input a:";
			cin >> ch >> t1;
			while (t1 < 0 || t1 >= states) {
				cout << "Invalid Input!.Input Again\n";
				cout << "For state q" << i << " and input a:";
				cin >> ch >> t1;
			}
			cout << "For state q" << i << " and input b:";
			cin >> ch >> t2;
			while (t2 < 0 || t2 >= states) {
				cout << "Invalid Input!.Input Again\n";
				cout << "For state q" << i << " and input B:";
				cin >> ch >> t1;
			}
			input[i] = { i, t1, t2 };
		}
		Groups.resize(states);
		cout << "Enter number of accepting states:";
		cin >> states;
		for (int i = 0; i < states; ++i) {
			int t1;
			char ch;
			cout << "Enter accepting state number " << i + 1 << ":";
			cin >> ch >> t1;
			GroupNumber[t1] = 0;
		}
		for (int i = 0; i < input.size(); ++i) {
			if (GroupNumber[i] == 0) {
				Groups[0].push_back(input[i]);
			}
			else {
				Groups[1].push_back(input[i]);
			}
		}
	}

	void minimize() {
		while (flag) {
			flag = false;
			for (int i = 0; i < Groups.size(); ++i) {
				if (Groups[i].size() <= 1)
					continue;
				int t1 = Groups[i][0][0];
				int grp1 = GroupNumber[Groups[i][0][1]];
				int grp2 = GroupNumber[Groups[i][0][2]];
				unordered_set<int> st1;
				st1.insert(0);
				for (int j = 1; j < Groups[i].size(); ++j) {
					int currt1 = GroupNumber[Groups[i][j][1]];
					int currt2 = GroupNumber[Groups[i][j][2]];
					if (grp1 == currt1 && grp2 == currt2) {
						st1.insert(j);
					}
				}
				for (int j = 1; j < Groups[i].size(); ++j) {
					vector<vector<int>> v;
					if (st1.find(j) == st1.end()) {
						int currt1 = GroupNumber[Groups[i][j][1]];
						int currt2 = GroupNumber[Groups[i][j][2]];
						cout << Groups[i][j][0] << " " << currt1 << " " << currt2 << endl;
						v.push_back(Groups[i][j]);
						for (int k = 0; k < Groups[i].size(); ++k) {
							if (k != j)
								if (currt1 == GroupNumber[Groups[i][k][1]] && currt2 == GroupNumber[Groups[i][k][2]]) {
									v.push_back(Groups[i][k]);
								}
						}
						for (auto it : v) {
							Groups[newGroup].push_back(it);
						}
						newGroup++;
						flag = true;
						for (auto it : v) {
							for (int k = 0; k < Groups[i].size(); ++k) {
								if (Groups[i][k] == it) {
									GroupNumber[Groups[i][k][0]] = newGroup - 1;
									if (st1.find(Groups[i].size() - 1) != st1.end()) {
										st1.erase(Groups[i].size() - 1);
										st1.insert(k);
									}
									swap(Groups[i][k], Groups[i][Groups[i].size() - 1]);
									Groups[i].pop_back();
									j = 1;
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	void print() {
		for (int i = 0; i < Groups.size(); ++i) {
			if (Groups[i].size() == 0)
				continue;
			string ans;
			for (int j = 0; j < Groups[i].size(); ++j) {
				ans.push_back('q');
				ans.push_back(Groups[i][j][0] + '0');
			}
			stateConcatenation[i] = ans;
		}
		cout << "STATES\ta\tb" << endl;
		for (int i = 0; i < Groups.size(); ++i) {
			if (Groups[i].size() == 0)
				continue;
			cout << stateConcatenation[i] << "\t";
			cout << stateConcatenation[GroupNumber[Groups[i][0][1]]] << "\t" << stateConcatenation[GroupNumber[Groups[i][0][2]]] << endl;
		}
	}
};
