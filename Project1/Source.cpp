#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;





inline void debugMode(const char* in, const char* out) {
#ifndef ONLINE_JUDGE
	if (in) freopen(in, "r", stdin);
	if (out) freopen(out, "w", stdout);
#endif // ONLINE_JUDGE
}
#define N 10000000



int HK[N], L[N], K[1001];
void PP(int fst) {
	printf("GG");
	for (int i = fst; i != -1; i = L[i])printf(" %d(%d)", i, L[i]);
	puts("");
}




int main(int argc, char* argv[]) {
	//debugMode("input.txt", NULL);

	int teamQuan, tmp;
	for (int dataCount=1; scanf("%d", &teamQuan) != EOF;) {
		printf("Line #%d\n", dataCount++);
		// 設置隊伍
		fill(HK, HK + N, 0);
		for (int i = 1, teamSize; i <= teamQuan; i++) {
			scanf("%d", &teamSize);
			//int teamQuan
			for (int j = 0; j < teamSize; j++) {
				scanf("%d", &tmp);
				HK[tmp] = i;
			}
		}
		// 初始化
		fill(L, L + N, -1);
		fill(K, K + 1001, -1);
		// 排隊
		int fst=-1, lst=-1;
		for (char buff[20]; scanf("%s", buff); ) {
			// 加入隊伍
			if (buff[0] == 'E') {
				scanf("%d", &tmp);
				if (fst == -1) {
					fst = lst = tmp;
					if (HK[tmp])K[HK[tmp]] = tmp;
					L[tmp] = -1;
				} else if (K[HK[tmp]] != -1 && K[HK[tmp]] != lst) {
					L[tmp] = L[K[HK[tmp]]];
					K[HK[tmp]] = L[K[HK[tmp]]] = tmp;
				} else {
					lst = L[lst] = tmp;
					if (HK[tmp])K[HK[tmp]] = tmp;
					L[tmp] = -1;
				}
			// 離開隊伍
			} else if (buff[0] == 'D') {
				if (fst == K[HK[fst]])
					K[HK[fst]] = -1;
				printf("%d\n", fst);
				fst = L[fst];
			} else if (buff[0] == 'S')
				break;
			// debug
			//PP(fst);
		}
	}
	//system("pause");
	return 0;
}