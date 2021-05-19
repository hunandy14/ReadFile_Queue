#pragma once
#include <iostream>
#include <map>
#include <list>
#include <queue>
using namespace std;

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
// ���]�n�X�βV�X�A�H�ά��u�����i���X
void test_TeamList_inout() {
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