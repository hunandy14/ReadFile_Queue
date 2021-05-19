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
	// ����s��
	if (debug) cout << "[" << idx << "]�s��::" << endl;
	size_t groupSize = line.getIntIdx(0);
	size_t gp_idx = groupSize;
	// �s�զW��
	if (debug) cout << "  �s�զW��::" << endl;
	for (int i = 0; i < groupSize; i++) {
		line.getline();
		vector<string_view>&& tokenList = line;
		// �إ߶���d�ߪ�
		groupTable.createTable(line);
		if (debug) cout << "    " << line << endl;
	}
	//checkMap(groupTable);

	// �������p
	if (debug) cout << "  �������p::" << endl;
	for (int i = 0; line.getline(); ++i) {
		if (line.getStringIdx(0) == "STOP") { break; }
		if (debug) cout << "    " << line << endl;

		// ���X�ƾ�
		string cmd = line.getStringIdx(0);

		// ����
		if (cmd == "ENQUEUE") {
			int id = line.getIntIdx(1);
			auto iter = groupTable.find(id);
			//if(debug)  cout << id << endl;

			if (iter != groupTable.end()) {
				//if(debug)  cout << "���" << iter->first << "->" <<iter->second << endl;
				teamList.ENQUEUE(iter->second, iter->first);
			} else {
				//if(debug)  cout << "�S�Ϊ���H" << endl;
				teamList.ENQUEUE(gp_idx++, id);
			}
		}
		// �e�������
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
