#include <iostream>
#include <map>
#include <list>
#include <queue>
#include "ReadFile.hpp"
using namespace std;

// 隊伍查詢表
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

	// 獲取群組
	cout << "[" << idx << "]群組::" << endl;

	size_t groupSize = line.getIntIdx(0);
	// 群組名單
	cout << "  群組名單::" << endl;
	groupTable.clear();
	for (int i = 0; i < groupSize; i++) {
		line.getline();
		vector<string_view>&& tokenList = line;
		// 建立隊伍查詢表
		createTable(line);
		cout << "    " << line << endl;
	}
	//checkMap(groupTable);

	// 插隊狀況
	cout << "  插隊狀況::" << endl;
	for (int i = 0; line.getline(); ++i) {
		if (line.getStringIdx(0) == "STOP") { break; }
		vector<string_view>&& tokenList = line;
		cout << "    " << tokenList << endl;
	}

	//if (!line.getline()){return 1;}
	return 0;
}

class Team {
public:
	Team(int name) :teamName(name) {}
	operator int() {
		return teamName;
	}

	void setName(int id) {
		this->teamName = id;
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
		list<Team>::iterator it = findTeam(teamName);
		if (it != data.end()) {
			//cout << "#### 1" << endl;
			it->ENQUEUE(id);
		}
		// 團隊不存在
		else {
			//cout << "#### 2" << endl;
			Team t(teamName);
			t.ENQUEUE(id);
			data.push_back(t);
		}
	}
	bool DEQUEUE(int& peple, bool pri=0) {
		// 檢查陣列是否正常有東西
		if (data.size()>0) 	{
			Team& t = data.front();
			if (t.DEQUEUE(peple)) { // 團隊內還有人
				//cout << "這團有人" << endl;
				if (pri) 	{
					cout << "[" << t.getName() << "]-" << peple << endl;
				}
				return 1;
			} else 	{
				//cout << "這團沒人，砍掉團名，再呼叫一次自己" << endl;
				data.pop_front();
				DEQUEUE(peple, pri);
			}
		}
		// 沒團隊了
		else 	{
			//cout << "鎮列為0" << endl;
			return 0;
		}

		return 0;
	}
	list<Team>::iterator findTeam(int teamName) {
		list<Team>::iterator it = data.begin();
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
void testll1() {
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
void testll2() {
	int p = -1;
	TeamList l;
	l.ENQUEUE(3, 6);
	l.DEQUEUE(p, 1);
	l.ENQUEUE(0, 1);
	l.ENQUEUE(1, 3);
	l.ENQUEUE(0, 2);
	l.ENQUEUE(2, 5);

	l.DEQUEUE(p, 1);
	l.DEQUEUE(p, 1);
	l.DEQUEUE(p, 1);
	l.DEQUEUE(p, 1);
	l.ENQUEUE(1, 4);// 晚到沒插到隊
	l.DEQUEUE(p, 1);
}


void test1() {
	OneLine line;
	line.openFile("in.txt");
	testOneData(line, 0);
	//for (int i=0; !testOneData(line, i); ++i) {}
}
//====================================================================================
int main(int argc, char const* argv[]) {
	test1();
	//testll1();
	//testll2();
	return 0;
}
//====================================================================================
