#include <iostream>
#include "Team.hpp"
#include "TeamTable.hpp"
using namespace std;


GroupTable groupTable;
TeamList teamList;
vector<int> sequence;
bool testOneData2(OneLine& line, int idx) {
	groupTable.clear();
	sequence.clear();
	bool debug = 0;

	if (!line.getline()) { return 1; }
	// 獲取群組
	if (debug) cout << "[" << idx << "]群組::" << endl;
	size_t groupSize = line.getIntIdx(0);
	size_t gp_idx = groupSize;
	// 群組名單
	if (debug) cout << "  群組名單::" << endl;
	for (int i = 0; i < groupSize; i++) {
		line.getline();
		vector<string_view>&& tokenList = line;
		// 建立隊伍查詢表
		groupTable.createTable(line);
		if (debug) cout << "    " << line << endl;
	}
	//checkMap(groupTable);

	// 插隊狀況
	if (debug) cout << "  插隊狀況::" << endl;
	for (int i = 0; line.getline(); ++i) {
		if (line.getStringIdx(0) == "STOP") { break; }
		if (debug) cout << "    " << line << endl;

		// 取出數據
		string cmd = line.getStringIdx(0);

		// 插隊
		if (cmd == "ENQUEUE") {
			int id = line.getIntIdx(1);
			auto iter = groupTable.find(id);
			//if(debug)  cout << id << endl;

			if (iter != groupTable.end()) {
				//if(debug)  cout << "找到" << iter->first << "->" <<iter->second << endl;
				teamList.ENQUEUE(iter->second, iter->first);
			} else {
				//if(debug)  cout << "沒團的單人" << endl;
				teamList.ENQUEUE(gp_idx++, id);
			}
		}
		// 前面的領到
		else if (cmd == "DEQUEUE") {
			int peple_idx = -1;
			if (debug)  cout << "------";
			teamList.DEQUEUE(peple_idx, debug);
			sequence.push_back(peple_idx);
		}
	}
	return 0;
}
//====================================================================================
int main(int argc, char const* argv[]) {
	OneLine line;
	line.openFile("in.txt");
	for (int i = 0; !testOneData2(line, i); ++i) {
		for (auto&& i : sequence) {
			cout << i << ", ";
		} cout << endl;
	}
	return 0;
}
//====================================================================================
