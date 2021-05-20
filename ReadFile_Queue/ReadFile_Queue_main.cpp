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
	// �����l���]�w��
	void readhead(const int& idx) {
		// ����s��
		if (debug) cout << "[" << idx << "]�s��::" << endl;
		groupSize = line.getIntIdx(0);
		groupCount = groupSize;
		// �s�զW��
		if (debug) cout << "  �s�զW��::" << endl;
		for (int i = 0; i < groupSize; i++) {
			line.getline();
			vector<string> str = line;
			groupTable.createTable(str); // �إ߶���d�ߪ�
			if (debug) cout << "    " << line << endl;
		}
		//checkMap(groupTable);
	}
	// �̾کR�O �����άO���o
	void queue(string cmd) {
		if (cmd == "ENQUEUE") { // ����
			int id = line.getIntIdx(1);
			auto iter = groupTable.find(id);
			if (iter != groupTable.end()) { // ���Ϊ��H
				teamList.ENQUEUE(iter->second, iter->first);
			} else { // �S�Ϊ���H
				teamList.ENQUEUE(groupCount++, id);
			}
		} else if (cmd == "DEQUEUE") { // �e�������F
			int peple_idx = -1; // �����O�ֻ��F
			if (debug)  cout << "------";
			teamList.DEQUEUE(peple_idx, debug);
			sequence.push_back(peple_idx);
		}
	}
	// ����R�O
	bool inpuCmd(OneLine& line, const int& idx) {
		if (!line.getline()) { return 1; }
		groupTable.clear();
		sequence.clear();
		// ����]�w��
		readhead(idx);
		// �������p
		if (debug) cout << "  �������p::" << endl;
		for (int i = 0; line.getline(); ++i) {
			if (line.getStringIdx(0) == "STOP") { break; }
			if (debug) cout << "    " << line << endl;
			// ���X�ƾ�
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
