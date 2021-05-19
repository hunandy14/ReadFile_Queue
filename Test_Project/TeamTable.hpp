#pragma once
#include <iostream>
#include <map>
#include "ReadFile.hpp"
using namespace std;

class GroupTable {
private:
	using _tepe = map<int, int>;
public:
	GroupTable() : groupCont(0) {}
	operator _tepe() {
		return data;
	}
public:
	// �̧Ǩ��X�Ҧ��C�������H
	void checkMap(_tepe table) {
		for (auto&& it = table.begin(); it != table.end(); ++it)
			cout << it->first << " => " << it->second << '\n';
	}
	// �ھڶ��ͩR�O�]�w �@����̭�����
	void createTable(OneLine& line) {
		for (size_t i = 1; i < line.size(); i++) {
			int num = line.getIntIdx(i);
			data[num] = groupCont;
		}
		groupCont++;
	}
	size_t size() {
		return groupCont;
	}
	void clear() {
		data.clear();
	}
	_tepe::iterator find(const int& id) {
		return data.find(id);
	}
	_tepe::iterator end() {
		return data.end();
	}
private:
	int groupCont;
	_tepe data;
};