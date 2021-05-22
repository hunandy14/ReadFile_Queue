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
	bool debug = 0;			// �}�Ұ����ο�X
	bool output = 1;		// �}�ҧ@���Ҧ��̷��D�ػݨD��X
protected:
	OneLine line;			// Ū���ɮ�+���Φr��֤�
};

class Queue: public Unity{
public:
	Queue() {}
public:
	// �]�m����d�ߪ�
	void cmd_setGroupTable(OneLine& line, const size_t& groupAmount) {
		for (size_t i = 0; i < groupAmount; i++) {
			line.readNextLine();
			vector<int> list = line;
			if (debug) cout << "    " << line << endl;
			groupTable.addGroup(list, 1);
		}
	}
	// ����ƶ����X�R�O
	bool cmd_exec(OneLine& line) {
		string cmd(line[0]);
		if (cmd == "ENQUEUE") { // ����
			int id = (int)line.getIntIdx(1);
			auto iter = groupTable.find(id);
			if (iter != groupTable.end()) { // ���Ϊ��H
				if (debug) cout << " [" << iter->first << "-> " << iter->second << " ]";
				teamList.ENQUEUE(iter->second, iter->first);
			} else { // �S�Ϊ���H
				int groupName = ++groupCount;
				if (debug) cout << " [" << id << "-> " << groupName << " ]new";
				teamList.ENQUEUE(groupName++, id);
			}
		} else if (cmd == "DEQUEUE") { // �e�������F
			int peple = -1; // �����O�ֻ��F
			//if (debug)  cout << "------";
			teamList.DEQUEUE(peple, debug);
			sequence.push_back(peple);
			if (output) printf("%d\n", peple);
		}
		return 0;
	}
	// �v��Ū���ð���
	bool runOneData() {
		// ���լO�_����ƥi����
		if (!line.readNextLine()) {return 0;}
		// ����s�զW��
		int groupQuantity = (int)line.getIntIdx(0);
		if (debug) cout << "[" << dataCount << "]��Ʋ�::" << endl;
		if (output) printf("Line #%d\n", dataCount+1);
		// �]�m����d�ߪ�
		cmd_setGroupTable(line, groupQuantity);
		groupCount = groupQuantity;
		// ����[�ƶ�, ���X]���R�O
		if (debug) cout << "  �������p::" << endl;
		for (int i = 0; line.readNextLine(); ++i) {
			if (line.getStringIdx(0) == "STOP") { ++dataCount;break; }
			if (debug) cout << "    " << line;
			// ���X�ƾ�
			cmd_exec(line);
			if (debug) cout << endl;
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
	int groupCount = 0;		// ����y����
	GroupTable groupTable;	// �s�լy������Ӫ�
	TeamList teamList;		// �ƶ�����
private:
	int dataCount = 0;		// ��Ʋժ��y����
	vector<int> sequence;	// �x�s���G
};
//====================================================================================
int main(int argc, char const* argv[]) {
	Queue ut;
	//ut.debugMode();
	ut.openFile("data.txt");
	ut.run();
	return 0;
}
//====================================================================================
