#pragma once
#include <iostream>
#include <map>
#include "ReadFile.hpp"
using namespace std;


#include <map>
// ����d�ߪ�
int groupCont;
using gp_t = map<int, int>;
gp_t groupTable;
void checkMap(gp_t groupTable) {
	for (gp_t::iterator it = groupTable.begin(); it != groupTable.end(); ++it)
		cout << it->first << " => " << it->second << '\n';
}
void createTable(OneLine& line) {
	for (size_t i = 1; i < line.size(); i++) {
		int num = line.getIntIdx(i);
		groupTable[num] = groupCont;
	}
	groupCont++;
}

bool testOneData(OneLine& line, int idx) {
	if (!line.getline()) { return 1; }

	// ����s��
	cout << "[" << idx << "]�s��::" << endl;

	size_t groupSize = line.getIntIdx(0);
	// �s�զW��
	cout << "  �s�զW��::" << endl;
	groupTable.clear();
	for (int i = 0; i < groupSize; i++) {
		line.getline();
		vector<string_view>&& tokenList = line;
		// �إ߶���d�ߪ�
		createTable(line);
		cout << "    " << line << endl;
	}
	//checkMap(groupTable);

	// �������p
	cout << "  �������p::" << endl;
	for (int i = 0; line.getline(); ++i) {
		if (line.getStringIdx(0) == "STOP") { break; }
		vector<string_view>&& tokenList = line;
		cout << "    " << tokenList << endl;
	}

	//if (!line.getline()){return 1;}
	return 0;
}

TeamList teamList;
vector<int> sequence;
bool testOneData2(OneLine& line, int idx) {
	if (!line.getline()) { return 1; }

	// ����s��
	cout << "[" << idx << "]�s��::" << endl;

	size_t groupSize = line.getIntIdx(0);
	size_t gp_idx = groupSize;
	// �s�զW��
	cout << "  �s�զW��::" << endl;
	groupTable.clear();
	for (int i = 0; i < groupSize; i++) {
		line.getline();
		vector<string_view>&& tokenList = line;
		// �إ߶���d�ߪ�
		createTable(line);
		cout << "    " << line << endl;
	}
	//checkMap(groupTable);

	// �������p
	cout << "  �������p::" << endl;
	for (int i = 0; line.getline(); ++i) {
		if (line.getStringIdx(0) == "STOP") { break; }
		vector<string_view>&& tokenList = line;
		cout << "    " << tokenList << endl;
		
		// ���X�ƾ�
		string cmd = line.getStringIdx(0);
		
		// ����
		if (cmd == "ENQUEUE") 	{
			int id = line.getIntIdx(1);
			auto iter = groupTable.find(id);
			//cout << id << endl;

			if (iter != groupTable.end()) 	{
				//cout << "���" << iter->first << "->" <<iter->second << endl;
				teamList.ENQUEUE(iter->second, iter->first);
			} else {
				//cout << "�S�Ϊ���H" << endl;
				teamList.ENQUEUE(gp_idx++, id);
			}
			//cout << "ENQUEUE=   " << it->first  << "-->" << it->second << endl;
			//teamList.ENQUEUE(cmd, id);
		}
		// �e�������
		else if (cmd == "DEQUEUE") 	{
			int peple_idx=-1;
			cout << "------";
			teamList.DEQUEUE(peple_idx, 1);
			sequence.push_back(peple_idx);
		}

	}
	return 0;
}