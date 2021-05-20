#include <iostream>
#include "ReadFile.hpp"
#include "Team.hpp"
#include "TeamTable.hpp"
using namespace std;



class Unity {
public:
	Unity(){}
	void openFile(const string& name) {
		line.openFile(name);
	}
public:
	void run(int count = -1) {
		for (int i = 0; count; ++i) {
			if (inpuCmd(line, i)) {break;}
			for (auto&& i : sequence) {
				cout << i << ", ";
			} cout << endl;
		}
	}
public:
	// 獲取初始的設定檔
	void readhead(const int& idx) {
		// 獲取群組
		if (debug) cout << "[" << idx << "]群組::" << endl;
		groupSize = line.getIntIdx(0);
		groupCount = groupSize;
		// 群組名單
		if (debug) cout << "  群組名單::" << endl;
		for (int i = 0; i < groupSize; i++) {
			line.getline();
			vector<string> str = line;
			groupTable.createTable(str); // 建立隊伍查詢表
			if (debug) cout << "    " << line << endl;
		}
		//checkMap(groupTable);
	}
	// 依據命令 插隊或是取得
	void queue(string cmd) {
		if (cmd == "ENQUEUE") { // 插隊
			int id = line.getIntIdx(1);
			auto iter = groupTable.find(id);
			if (iter != groupTable.end()) { // 有團的人
				teamList.ENQUEUE(iter->second, iter->first);
			} else { // 沒團的單人
				teamList.ENQUEUE(groupCount++, id);
			}
		} else if (cmd == "DEQUEUE") { // 前面的領到了
			int peple_idx = -1; // 接收是誰領到了
			if (debug)  cout << "------";
			teamList.DEQUEUE(peple_idx, debug);
			sequence.push_back(peple_idx);
		}
	}
	// 執行命令
	bool inpuCmd(OneLine& line, const int& idx) {
		if (!line.getline()) { return 1; }
		groupTable.clear();
		sequence.clear();
		// 獲取設定檔
		readhead(idx);
		// 插隊狀況
		if (debug) cout << "  插隊狀況::" << endl;
		for (int i = 0; line.getline(); ++i) {
			if (line.getStringIdx(0) == "STOP") { break; }
			if (debug) cout << "    " << line << endl;
			// 取出數據
			string cmd = line.getStringIdx(0);
			queue(cmd);
		}
		return 0;
	}
private:
	OneLine line;
private:
	bool debug = 1;
	size_t groupCount = 0;
	size_t groupSize = 0;
	GroupTable groupTable;
	TeamList teamList;
	vector<int> sequence;
};

//====================================================================================
int main(int argc, char const* argv[]) {
	Unity ut;
	ut.openFile("data.txt");
	ut.run();
	return 0;
}
//====================================================================================
