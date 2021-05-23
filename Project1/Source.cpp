#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

inline void debugMode(const char* in, const char* out) {
	if (in) freopen(in, "r", stdin);
	if (out) freopen(out, "w", stdout);
}

#define N 10000000

int gp_id[N];		// ���ݪ�����N��
int nextId[N];		// ����id���᭱�ƪ��O��
int gp_fn[1001];	// ���ΤH���̫�O��
void PP(int fst) {
	printf("GG");
	for (int i = fst; i != -1; i = nextId[i])printf(" %d(%d)", i, nextId[i]);
	puts("");
}

int main(int argc, char* argv[]) {
	debugMode("in.txt", NULL);

	int tmp, teamQuan, teamSize;
	for (int dataCount = 1; scanf("%d", &teamQuan) != EOF;) {
		printf("Line #%d\n", dataCount++);
		// �]�m����
		fill(gp_id, gp_id + N, 0);
		for (int i = 1; i <= teamQuan; i++) {
			scanf("%d", &teamSize); // �������H��
			for (int j = 0; j < teamSize; j++) {
				scanf("%d", &tmp); // �������id
				gp_id[tmp] = i;
			}
		}
		// ��l��
		fill(nextId, nextId + N, -1);
		fill(gp_fn, gp_fn + 1001, -1);
		// �ƶ�
		int fst = -1;						// �`����Ĥ@��
		int lst = -1;						// �`����̫�@��
		for (char buff[20]; scanf("%s", buff); ) {
			// �[�J����
			if (buff[0] == 'E') {
				scanf("%d", &tmp); // ����ثe�ƤJ��id

				// -----------------------�]�w��--------------------------
				int& pp = tmp;					// �ӱƶ����s�H
				int& gpId = gp_id[pp];			// �o�ӤH���ݹ���
				int& gpFn = gp_fn[gpId];		// ����o�ӤH���ݹ��骺�̫�@�ӤH��id

				int& pp_nt = nextId[pp];		// �o�ӷs�H�᭱�ƪ��H
				int& gpFn_nt = nextId[gpFn];	// �ۤv�γ̫�@�ӤH���U�@�ӤH
				// ------------------------------------------------------
				// �S�H�b�ƶ�
				if (fst == -1) {
					fst = lst = pp;		// �`�����Y�����O�ۤv
					if (gpId) {			// �����ݹ���
						gpFn = pp;		// �o�ӤH���O�W��L -> �аO�ۤv�O����o�Ϊ��̫�@��
					}
					pp_nt = -1;			// �L�᭱�S�H

				// ���ۤv�H�b�ƶ��B�ۤv�H�b�e�� --> �i�H����
				} else if (gpFn != -1 && gpFn != lst) {
					pp_nt = gpFn_nt;	// ����1::�ۤv���᭱ = �ۤv�γ̫�@�ӤH���U�@�ӤH
					gpFn_nt = pp;		// ����2::�ƨ�ۤv�Ϊ��̫�@�ӤH��
					gpFn = pp;			// �ۤv�O�o�Ϊ��̫�@�ӤH

				// �S�ۤv�H�b�ƶ��Φۤv�H�N�b�᭱ --> �Ĩıƶ�
				} else {
					nextId[lst] = pp;	// �ƨ��`����̫�@�ӤH�᭱
					lst = pp;			// �ܦ�����̫�@�ӤH
					if (gpId) {			// �����ݹ���
						gpFn = pp;		// �o�ӤH���O�W��L -> �аO�ۤv�O����o�Ϊ��̫�@��
					}	
					pp_nt = -1;			// �o�ӷs�H�᭱�S�H�F
				}
			// ���}����
			} else if (buff[0] == 'D') {
				// -----------------------�]�w��--------------------------
				int& fst_gp	  = gp_id[fst];		// �ثe�̫e�������骺�N��
				int& fst_gpFn = gp_fn[fst_gp];	// �`����Ĥ@��::�ثe�̫e�������骺�̫�@�ӤH
				// ------------------------------------------------------
				if (fst == fst_gpFn){
					fst_gpFn = -1;				// ���餤���̫�@�Ө��F(�᭱�A�ӦP�Ϊ����ഡ�F)
				} 
				printf("%d\n", fst);
				fst = nextId[fst];				// �`����Ĥ@�Ӯ���F�訫�F
			} else if (buff[0] == 'S')
				break;
			//PP(fst);
		}
	}
	//system("pause");
	return 0;
}