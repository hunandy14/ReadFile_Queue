#include <iostream>
#include <map>
#include <list>
#include <queue>
#include "ReadFile.hpp"
using namespace std;

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
		// �ζ��w�g�s�b
		list<Team>::iterator it = findTeam(teamName);
		if (it != data.end()) {
			//cout << "#### 1" << endl;
			it->ENQUEUE(id);
		}
		// �ζ����s�b
		else {
			//cout << "#### 2" << endl;
			Team t(teamName);
			t.ENQUEUE(id);
			data.push_back(t);
		}
	}
	bool DEQUEUE(int& peple, bool pri=0) {
		// �ˬd�}�C�O�_���`���F��
		if (data.size()>0) 	{
			Team& t = data.front();
			if (t.DEQUEUE(peple)) { // �ζ����٦��H
				//cout << "�o�Φ��H" << endl;
				if (pri) 	{
					cout << "[" << t.getName() << "]-" << peple << endl;
				}
				return 1;
			} else 	{
				//cout << "�o�ΨS�H�A�屼�ΦW�A�A�I�s�@���ۤv" << endl;
				data.pop_front();
				DEQUEUE(peple, pri);
			}
		}
		// �S�ζ��F
		else 	{
			//cout << "��C��0" << endl;
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

// ���չζ����i���X
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
// ���]�n�X�βV�X�A�H�ά��u�����i���X
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
	l.ENQUEUE(1, 4);// �ߨ�S���춤
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
