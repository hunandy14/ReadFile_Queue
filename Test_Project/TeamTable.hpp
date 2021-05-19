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