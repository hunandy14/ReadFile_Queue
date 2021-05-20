#include <iostream>
#include "ReadFile.hpp"
#include "Team.hpp"
#include "TeamTable.hpp"
using namespace std;

class Unity {
public:
	Unity() {}
	void openFile(const string& name) {
		line.openFile(name);
	}
public:
	// 設置隊伍查詢表
	void cmd_setGroupTable(const size_t& groupAmount, OneLine& line) {
		for (size_t i = 0; i < groupAmount; i++) {
			line.readNextLine();
			vector<int> list = line;
			if (debug) cout << "    " << line << endl;
			groupTable.addGroup(list, 1);
		}
	}
	// 執行排隊取出命令
	bool cmd_exec(OneLine& line) {
		string_view cmd = line[0];
		if (cmd == "ENQUEUE") { // 插隊
			int id = line.getIntIdx(1);
			auto iter = groupTable.find(id);
			if (iter != groupTable.end()) { // 有團的人
				teamList.ENQUEUE(iter->second, iter->first);
			} else { // 沒團的單人
				teamList.ENQUEUE(groupCount++, id);
			}
		} else if (cmd == "DEQUEUE") { // 前面的領到了
			int peple = -1; // 接收是誰領到了
			if (debug)  cout << "------";
			teamList.DEQUEUE(peple, debug);
			sequence.push_back(peple);
			if (output) printf("%d\n", peple);
		}
		return 0;
	}
public:
	// 逐行讀取並執行
	void cmder(int count = -1) {
		line.readNextLine();
		// 獲取群組名單
		int groupAmount = line.getIntIdx(0);
		if (debug) cout << "[" << groupAmount << "]群組::" << endl;
		if (output) printf("Line #%d\n", groupAmount);
		// 設置隊伍查詢表
		cmd_setGroupTable(groupAmount, line);
		// 執行排隊取出命令
		if (debug) cout << "  插隊狀況::" << endl;
		for (int i = 0; line.readNextLine(); ++i) {
			if (line.getStringIdx(0) == "STOP") { break; }
			if (debug) cout << "    " << line << endl;
			// 取出數據
			cmd_exec(line);
		}
	}
private:
	bool debug = 1;			// 開啟除錯用輸出
	bool output = 0;		// 開啟作答模式依照題目需求輸出
private:
	OneLine line;			// 讀取檔案+切割字串核心
private:
	size_t groupCount = 0;	// 群組的流水號
	GroupTable groupTable;	// 群組流水號對照表
	TeamList teamList;		// 排隊隊伍
private:
	vector<int> sequence;	// 儲存結果
};

class Queue {
public:
	Queue() {}

private:

};

#include <charconv>
#include <optional>
//====================================================================================
int main(int argc, char const* argv[]) {
	Unity ut;
	ut.openFile("data.txt");
	//ut.run();
	ut.cmder();
	//std::optional<int> opt;
	//cout << *opt << endl;
	return 0;
}
//====================================================================================
