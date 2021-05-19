#pragma once
#include <iostream>
#include <map>
#include "ReadFile.hpp"
using namespace std;


#include <map>

class GroupTable 				{
public:

private:

};
// 隊伍查詢表
int groupCont;
map<int, int> groupTable;
// 依序取出所有列隊中的人
void checkMap(map<int, int> table) {
	for (auto&& it = table.begin(); it != table.end(); ++it)
		cout << it->first << " => " << it->second << '\n';
}
// 根據隊友命令設定 一隊伍裡面有誰
void createTable(OneLine& line) {
	for (size_t i = 1; i < line.size(); i++) {
		int num = line.getIntIdx(i);
		groupTable[num] = groupCont;
	}
	groupCont++;
}

bool testOneData(OneLine& line, int idx) {
	if (!line.getline()) { return 1; }

	// 獲取群組
	cout << "[" << idx << "]群組::" << endl;

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
	for (int i = 0; line.getline(); ++i) {
		if (line.getStringIdx(0) == "STOP") { break; }
		vector<string_view>&& tokenList = line;
		cout << "    " << tokenList << endl;
	}

	//if (!line.getline()){return 1;}
	return 0;
}

