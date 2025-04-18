#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main() {

	vector<vector<int>> input; //state  a   b
	unordered_map<int, int> GroupNumber;  //key=state   val=grouping

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
		input.push_back({ i, t1, t2 });    //index   a   b 

		GroupNumber[i] = 1;   //by default sab ko 1 baad mein initial mein 0 dedenge
	}

	vector<vector<vector<int>>> Groups(states);  //max groups bnaliye  max possible states==saare hi tut jayen, no common state


	cout << "Enter number of accepting states:";
	cin >> states;
	for (int i = 0; i < states; ++i) {
		int t1;
		char ch;
		cout << "Enter accepting state number " << i + 1 << ":";
		cin >> ch >> t1;
		GroupNumber[t1] = 0;  //baad mein manually mark krdia in map with 0
	}

	for (int i = 0; i < input.size(); ++i) { 
		if (GroupNumber[i] == 0) {   //agar map val 0 de to final mein pushback
			Groups[0].push_back(input[i]);
		}
		else { //warna initial mein pushback
			Groups[1].push_back(input[i]);
		}
	}
	int newGroup = 2; //groups mein wese indexes state k brabar honge but occupy abhi 2 hwe hain initial and final
	bool flag = true;
	while (flag) {
		flag = false;
		for (int i = 0; i < Groups.size(); ++i) {

			if (Groups[i].size() <= 1)  //already minimal ya khaali index
				continue; //skip

			int t1 = Groups[i][0][0];  //state
			int grp1 = GroupNumber[Groups[i][0][1]];  //a
			int grp2 = GroupNumber[Groups[i][0][2]];  //b
			unordered_set<int> st1;
			st1.insert(0);  //manually 0 daaldia baad mein pta chlega kyun


			for (int j = 1; j < Groups[i].size(); ++j) {  //aik index k agle value pr jese agar {1,2,3} hai to j=2 and i=1 initially
				int currt1 = GroupNumber[Groups[i][j][1]];  //agle wale k a ka groupnumber
				int currt2 = GroupNumber[Groups[i][j][2]];  //agle wale k b ka groupnumber
				if (grp1 == currt1 && grp2 == currt2) {   //agar same group se belong to insert in set
					st1.insert(j);
				}
			}
			for (int j = 1; j < Groups[i].size(); ++j) {
				vector<vector<int>> v;

				if (st1.find(j) == st1.end()) {  //nhi mila, split hona chahiye ya nhi as agar same group mein hota to set mein hota agar nhi to split kro
					int currt1 = GroupNumber[Groups[i][j][1]];  //split hone wale ka a
					int currt2 = GroupNumber[Groups[i][j][2]];  //split hone wale ka b
					cout << Groups[i][j][0] << " " << currt1 << " " << currt2 << endl;
					v.push_back(Groups[i][j]);  //as it is alag hone wali state utha k vector mein along with a and b 
					for (int k = 0; k < Groups[i].size(); ++k) {
						if (k != j) //agar same state nahi hain
							if (currt1 == GroupNumber[Groups[i][k][1]] && currt2 == GroupNumber[Groups[i][k][2]]) {  //iske jaisa koi aur namoona hai(same groupnumber mein transition)? to same v1 mein daaldo pura utha along with transition vector
								v.push_back(Groups[i][k]);
							}
					}
					for (auto it : v) {
						Groups[newGroup].push_back(it); //naya group bangya by accessing new index jo pehle khaali tha
					}
					newGroup++;  //increment group number for key in map
					flag = true;
					for (auto it : v) { //for each v k index ka vector
						for (int k = 0; k < Groups[i].size(); ++k) {
							if (Groups[i][k] == it) { //match from the main group to remove
								GroupNumber[Groups[i][k][0]] = newGroup - 1; //assign new group number
								if (st1.find(Groups[i].size() - 1) != st1.end()) { //milgya
									st1.erase(Groups[i].size() - 1);
									st1.insert(k);
								}
								swap(Groups[i][k], Groups[i][Groups[i].size() - 1]); //swap krdo last index se taake popback krsken
								Groups[i].pop_back();

								j = 1; //wapis j reset
								break;
							}
						}
					}
				}
			}
		}
	}

	unordered_map<int, string> stateConcatenation;
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