#include <iostream>
#include "dfa.h"

using namespace std;

int main() {
	dfa dfa1(5);
	dfa1.takeinput();
	dfa1.minimize();
	dfa1.print();
	return 0;
}
