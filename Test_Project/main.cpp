#include <iostream>
#include <map>
#include <list>
#include <queue>
#include "ReadFile.hpp"
using namespace std;

// 隊伍查詢表
int groupCont;
using gp_t = map<int, int>;
gp_t groupTable;
void checkMap(gp_t groupTable) {
	for (gp_t::iterator it=groupTable.begin(); it!=groupTable.end(); ++it)
		cout << it->first << " => " << it->second << '\n';
}
void createTable(OneLine& line) {
	for (size_t i = 1; i < line.size(); i++) {
		int num = line.getIntIdx(i);
		groupTable[num] = groupCont;
	}
	groupCont++;
}

bool testOneData(OneLine& line, int idx) {
	if (!line.getline()){return 1;}

	// 獲取群組
	cout << "["<< idx <<"]群組::" << endl;

	size_t groupSize = line.getIntIdx(0);
	// 群組名單
	cout << "  群組名單::" << endl;
	groupTable.clear();
	for (int i = 0; i < groupSize; i++) {
		line.getline();
		vector<string_view>&& tokenList = line;
		// 建立隊伍查詢表
		createTable(line);
		cout << "    " << line << endl;
	}
	//checkMap(groupTable);

	// 插隊狀況
	cout << "  插隊狀況::" << endl;
	for (int i=0; line.getline(); ++i) {
		if (line.getStringIdx(0) == "STOP") {break;}
		vector<string_view>&& tokenList = line;
		cout << "    " << tokenList << endl;
	}

	//if (!line.getline()){return 1;}
	return 0;
}

void test1() {
	OneLine line;
	line.openFile("in.txt");
	testOneData(line, 0);
	//for (int i=0; !testOneData(line, i); ++i) {}
}

list<queue<int>> teamList;
queue<int> team;

//====================================================================================
int main(int argc, char const* argv[]) {
	//test1();
	team.push(1);
	team.push(2);
	team.push(3);
	cout << team.front() << endl;
	team.pop();
	cout << team.front() << endl;



	return 0;
}
//====================================================================================
