#include <iostream>
#include <climits>
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
	void setStatus(bool debug, bool output) {
		this->debug = debug;
		this->output = output;
	}
	void debugMode(){this->debug=1, this->output=0;}
	void outputMode(){this->debug=0, this->output=1;}
protected:
	bool debug = 0;			// 開啟除錯用輸出
	bool output = 1;		// 開啟作答模式依照題目需求輸出
protected:
	OneLine line;			// 讀取檔案+切割字串核心
};

class Queue: public Unity{
public:
	Queue() {}
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
		string cmd(line[0]);
		if (cmd == "ENQUEUE") { // 插隊
			int id = (int)line.getIntIdx(1);
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
	// 逐行讀取並執行
	bool runOneData() {
		// 測試是否有資料可執行
		if (!line.readNextLine()) {return 0;}
		// 獲取群組名單
		int groupAmount = (int)line.getIntIdx(0);
		if (debug) cout << "[" << groupCount << "]群組::" << endl;
		if (output) printf("Line #%d\n", dataCount+1);
		// 設置隊伍查詢表
		cmd_setGroupTable(groupAmount, line);
		// 執行排隊取出命令
		if (debug) cout << "  插隊狀況::" << endl;
		for (int i = 0; line.readNextLine(); ++i) {
			if (line.getStringIdx(0) == "STOP") { ++dataCount; break; }
			if (debug) cout << "    " << line << endl;
			// 取出數據
			cmd_exec(line);
		}
		return 1;
	}
public:
	void run(int count = INT_MAX) {
		for (int i = 0; i<count; i++) {
			if (!runOneData()) {
				break;
			}
		}
	}
private:
	int groupCount = 0;	// 群組的流水號
	GroupTable groupTable;	// 群組流水號對照表
	TeamList teamList;		// 排隊隊伍
private:
	int dataCount = 0;		// 總共跑了幾筆資料
	vector<int> sequence;	// 儲存結果
};
//====================================================================================
int main(int argc, char const* argv[]) {
	Queue ut;
	ut.debugMode();
	ut.openFile("data_test.txt");
	ut.run();
	return 0;
}
//====================================================================================
