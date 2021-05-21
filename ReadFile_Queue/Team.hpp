#pragma once
#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Team {
public:
	Team(int name) :teamName(name) {}
	operator int() {
		return teamName;
	}

	int getName() {
		return teamName;
	}
	void ENQUEUE(int n) {
		data.push(n);
	}
	bool DEQUEUE(int& num) {
		if (!data.empty()) {
			num = data.front();
			data.pop();
			return 1;
		}
		return 0;
	}
	bool empty() {
		if (data.empty())
			return 1;
		return 0;
	}
	void out() {
		cout << "  [" << teamName << "]::" << endl;
		cout << "    ";
		while (!data.empty()) {
			cout << data.front() << ", ";
			data.pop();
		} cout << endl;
	}
private:
	int teamName;
	queue<int> data;
};

class TeamList {
public:
	TeamList() = default;
	void ENQUEUE(int teamName, int id) {
		// 團隊已經存在
		auto&& it = findTeam(teamName);
		if (it != data.end()) {
			it->ENQUEUE(id);
		}
		// 團隊不存在
		else {
			Team t(teamName);
			t.ENQUEUE(id);
			data.push_back(t);
		}
	}
	bool DEQUEUE(int& peple, bool debug = 0) {
		// 檢查陣列是否正常有東西
		if (data.size() > 0) {
			Team& t = data.front();
			if (t.DEQUEUE(peple)) { // 團隊內還有人
				if (debug) cout << "[" << t.getName() << "]-" << peple << endl;
				return 1;
			} else { // 這團沒人了，砍掉之後重叫下一個
				data.pop_front();
				DEQUEUE(peple, debug);
			}
		}
		// 沒團隊了
		else { return 0; }
		return 0;
	}
	list<Team>::iterator findTeam(int teamName) {
		auto&& it = data.begin();
		for (; it != data.end(); ++it) {
			if (teamName == it->getName()) {
				return it;
			}
		}
		return it;
	}
	void out() {
		for (auto&& i : data) {
			i.out();
		} cout << endl;
	}
private:
	list<Team> data;
};

// 測試團隊先進先出
void test_Team_inout() {
	Team team(0);
	team.ENQUEUE(1);
	team.ENQUEUE(2);
	team.ENQUEUE(3);

	int p = -1;
	while (team.DEQUEUE(p)) {
		cout << p << endl;
	}
}
// 測設好幾團混合，以團為優先先進先出
void test_TeamList_inout() {
	int p = -1;
	TeamList l;
	l.ENQUEUE(3, 6);
	l.DEQUEUE(p, true);
	l.ENQUEUE(0, 1);
	l.ENQUEUE(1, 3);
	l.ENQUEUE(0, 2);
	l.ENQUEUE(2, 5);

	l.DEQUEUE(p, true);
	l.DEQUEUE(p, true);
	l.DEQUEUE(p, true);
	l.DEQUEUE(p, true);
	l.ENQUEUE(1, 4);// 晚到沒插到隊
	l.DEQUEUE(p, true);
}
