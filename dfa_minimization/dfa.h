#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
//#include "state.h"
using namespace std;

class dfa {
    int numofstates;
    int numofsymbols;
    vector<char> symbols;
    vector<vector<int>> input;
    vector<vector<vector<int>>> groups;
    unordered_map<int,int> groupnumber;

public:
    dfa(int numofstates, int numofsymbols) {
        this->numofstates = numofstates;
        this->numofsymbols = numofsymbols;
        groups.resize(numofstates);
    }

    void takeinput() {
        int finalstates;
        int s;
        char ch;

        for (int i = 0; i < numofstates; i++) {
            int t;
            char ch;
            for (int j = 0; j < numofsymbols; j++) {
                cout << "For state q" << i << " and input symbol " << symbols[j] << ": ";
                cin >> ch >> t;
                while (t < 0 || t >= numofstates) {
                    cout << "Invalid Input!.Input Again\n";
                    cout << "For state q" << i << " and input symbol " << symbols[j] << ": ";
                    cin >> ch >> t;
                }
                input[i].push_back(j);
            }

            groupnumber[i] = 1;
        }

        cout << "Enter number of final states:";
        cin >> finalstates;
        for (int i = 0; i < finalstates; i++) {
            cout << "Enter accepting state number " << i + 1 << ":";
            cin >> ch >> s;
            groupnumber[s] = 0;
        }
    }
};
