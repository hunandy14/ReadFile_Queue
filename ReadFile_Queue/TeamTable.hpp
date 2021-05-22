#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class GroupTable {
private:
	using _tepe = map<int, int>;
public:
	GroupTable() : groupSize(0) {}
	operator _tepe() {
		return _data;
	}
public:
	// 依序取出所有列隊中的人
	void checkTable() {
		for (auto&& it = _data.begin(); it != _data.end(); ++it)
			cout << it->first << " => " << it->second << '\n';
	}
	// 設定一組隊伍(對應到同一組UID)
	void addGroup(const vector<int>& group, int start = 0, int end = -1) {
		if (end < 0)
			end = (int)group.size();
		for (size_t i = 1; i < end; i++) {
			_data[group[i]] = groupSize;
		}
		++groupSize;
	}
	// 設定沒隊伍的單人
	void addSingle(const int& key) {
		_data[key] = groupSize;
		++groupSize;
	}

	size_t groupCount() {
		return groupSize;
	}
	void clear() {
		_data.clear();
	}
	_tepe::iterator find(const int& id) {
		return _data.find(id);
	}
	_tepe::iterator end() {
		return _data.end();
	}
private:
	int groupSize; // 隊伍流水號，同時也表示存在幾組隊伍
	_tepe _data;
};


void gt_test_addgp() {
	GroupTable gp;

	vector<int> v{5, 1, 2, 3, 4, 5};
	gp.addGroup(v, 1);

	vector<int> v2{5, 6, 7, 8, 9, 10};
	gp.addGroup(v2, 1);

	gp.addSingle(11);
	gp.checkTable();
}
