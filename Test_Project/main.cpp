#include <iostream>
#include "Team.hpp"
#include "TeamTable.hpp"
using namespace std;



TeamList teamList;
vector<int> sequence;
bool testOneData2(OneLine& line, int idx) {
	if (!line.getline()) { return 1; }

	// 獲取群組
	cout << "[" << idx << "]群組::" << endl;

	size_t groupSize = line.getIntIdx(0);
	size_t gp_idx = groupSize;
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
	for (int i = 0; line.getline(); ++i) {
		if (line.getStringIdx(0) == "STOP") { break; }
		vector<string_view>&& tokenList = line;
		cout << "    " << tokenList << endl;

		// 取出數據
		string cmd = line.getStringIdx(0);

		// 插隊
		if (cmd == "ENQUEUE") 	{
			int id = line.getIntIdx(1);
			auto iter = groupTable.find(id);
			//cout << id << endl;

			if (iter != groupTable.end()) 	{
				//cout << "找到" << iter->first << "->" <<iter->second << endl;
				teamList.ENQUEUE(iter->second, iter->first);
			} else {
				//cout << "沒團的單人" << endl;
				teamList.ENQUEUE(gp_idx++, id);
			}
			//cout << "ENQUEUE=   " << it->first  << "-->" << it->second << endl;
			//teamList.ENQUEUE(cmd, id);
		}
		// 前面的領到
		else if (cmd == "DEQUEUE") 	{
			int peple_idx=-1;
			cout << "------";
			teamList.DEQUEUE(peple_idx, 1);
			sequence.push_back(peple_idx);
		}

	}
	return 0;
}

void test1() {
	OneLine line;
	line.openFile("in.txt");
	testOneData2(line, 0);
	testOneData2(line, 0);
	//for (int i=0; !testOneData(line, i); ++i) {}
}

void allTest() {
	test_Team_inout();
	test_TeamList_inout();
	rf_test_getIdx();
	test_TeamList_inout();
}
//====================================================================================
int main(int argc, char const* argv[]) {
	test1();

	return 0;
}
//====================================================================================
