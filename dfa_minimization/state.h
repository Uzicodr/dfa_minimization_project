#pragma once
#include<iostream>
using namespace std;

class state
{
private:
	bool initialstate;
	bool finalstate;
	int number;

public:
	state(int num, bool final_state, bool initial_state) {
		number = num;
		initialstate = initial_state;
		finalstate = final_state;
	}

	bool isfinal() {
		if (finalstate == true) {
			return true;
		}
		return false;
	}

	bool isinitial() {
		if (initialstate == true) {
			return true;
		}
		return false;
	}
};

