#include <iostream>
#include "Team.hpp"
#include "TeamTable.hpp"
using namespace std;



void test1() {
	OneLine line;
	line.openFile("in.txt");
	testOneData(line, 0);
	//for (int i=0; !testOneData(line, i); ++i) {}
}

void allTest() {
	test_Team_inout();
	test_TeamList_inout();
}
//====================================================================================
int main(int argc, char const* argv[]) {
	test1();



	return 0;
}
//====================================================================================
