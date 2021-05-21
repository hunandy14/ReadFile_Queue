#pragma once
#include <iostream>
#include <string>
#include <string_view>
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
	void addSingle(const int& key, const int& value) {
		_data[key] = value;
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
	int groupSize; // 當前表中有幾組不同的隊伍
	_tepe _data;
};
