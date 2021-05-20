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
	// �]�m����d�ߪ�
	void cmd_setGroupTable(const size_t& groupAmount, OneLine& line) {
		for (size_t i = 0; i < groupAmount; i++) {
			line.readNextLine();
			vector<int> list = line;
			if (debug) cout << "    " << line << endl;
			groupTable.addGroup(list, 1);
		}
	}
	// ����ƶ����X�R�O
	bool cmd_exec(OneLine& line) {
		string_view cmd = line[0];
		if (cmd == "ENQUEUE") { // ����
			int id = line.getIntIdx(1);
			auto iter = groupTable.find(id);
			if (iter != groupTable.end()) { // ���Ϊ��H
				teamList.ENQUEUE(iter->second, iter->first);
			} else { // �S�Ϊ���H
				teamList.ENQUEUE(groupCount++, id);
			}
		} else if (cmd == "DEQUEUE") { // �e�������F
			int peple = -1; // �����O�ֻ��F
			if (debug)  cout << "------";
			teamList.DEQUEUE(peple, debug);
			sequence.push_back(peple);
			if (output) printf("%d\n", peple);
		}
		return 0;
	}
public:
	// �v��Ū���ð���
	void cmder(int count = -1) {
		line.readNextLine();
		// ����s�զW��
		int groupAmount = line.getIntIdx(0);
		if (debug) cout << "[" << groupAmount << "]�s��::" << endl;
		if (output) printf("Line #%d\n", groupAmount);
		// �]�m����d�ߪ�
		cmd_setGroupTable(groupAmount, line);
		// ����ƶ����X�R�O
		if (debug) cout << "  �������p::" << endl;
		for (int i = 0; line.readNextLine(); ++i) {
			if (line.getStringIdx(0) == "STOP") { break; }
			if (debug) cout << "    " << line << endl;
			// ���X�ƾ�
			cmd_exec(line);
		}
	}
private:
	bool debug = 1;			// �}�Ұ����ο�X
	bool output = 0;		// �}�ҧ@���Ҧ��̷��D�ػݨD��X
private:
	OneLine line;			// Ū���ɮ�+���Φr��֤�
private:
	size_t groupCount = 0;	// �s�ժ��y����
	GroupTable groupTable;	// �s�լy������Ӫ�
	TeamList teamList;		// �ƶ�����
private:
	vector<int> sequence;	// �x�s���G
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
