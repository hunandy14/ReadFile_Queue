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



int gp_id[N]; // id -> 團體編號
int nextId[N]; // 那個id的後面排的是誰
int gp_fn[1001]; // 那團人的最後是誰
void PP(int fst) {
	printf("GG");
	for (int i = fst; i != -1; i = nextId[i])printf(" %d(%d)", i, nextId[i]);
	puts("");
}




int main(int argc, char* argv[]) {
	//debugMode("in.txt", NULL);

	int tmp, teamQuan, teamSize;
	for (int dataCount=1; scanf("%d", &teamQuan) != EOF;) {
		printf("Line #%d\n", dataCount++);
		// 設置團體
		fill(gp_id, gp_id + N, 0);
		for (int i = 1; i <= teamQuan; i++) {
			scanf("%d", &teamSize); // 獲取隊伍人數
			for (int j = 0; j < teamSize; j++) {
				scanf("%d", &tmp); // 獲取隊員id
				gp_id[tmp] = i;
			}
		}
		// 初始化
		fill(nextId, nextId + N, -1);
		fill(gp_fn, gp_fn + 1001, -1);
		// 排隊
		int fst=-1;
		int lst=-1;
		for (char buff[20]; scanf("%s", buff); ) {
			// 加入隊伍
			if (buff[0] == 'E') {
				scanf("%d", &tmp); // 獲取目前排入的id
				int gpId = gp_id[tmp]; // 這個人所屬團體
				int gpFnPid = gp_fn[gpId];
				

				// 沒人在排隊
				if (fst == -1) {
					fst = lst = tmp; // 總隊伍頭尾都是他
					if (gpId) { // 查表看有沒有所屬團體
						gp_fn[gpId] = tmp; // 只有他個就在尾端
					}
					nextId[tmp] = -1; // 他後面沒人

				// 有自己人在排隊且自己人在前面 --> 可以插隊
				} else if (gpFnPid != -1 && gpFnPid != lst) {
					nextId[tmp] = nextId[gpFnPid];
					gp_fn[gpId] = nextId[gpFnPid] = tmp;

				// 沒自己人在排隊或自己人就在後面 --> 乖乖排隊
				} else {
					lst = nextId[lst] = tmp;
					if (gpId)
						gp_fn[gpId] = tmp;
					nextId[tmp] = -1;
				}
			// 離開隊伍
			} else if (buff[0] == 'D') {
				if (fst == gp_fn[gp_id[fst]])
					gp_fn[gp_id[fst]] = -1;
				printf("%d\n", fst);
				fst = nextId[fst];
			} else if (buff[0] == 'S')
				break;
			// debug
			//PP(fst);
		}
	}
	//system("pause");
	return 0;
}