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
		int fst=-1;						// 總隊伍的第一個
		int lst=-1;						// 總隊伍的最後一個
		for (char buff[20]; scanf("%s", buff); ) {
			// 加入隊伍
			if (buff[0] == 'E') {
				scanf("%d", &tmp); // 獲取目前排入的id

				// -----------------------設定值--------------------------
				int& pp   = tmp;				// 來排隊的新人
				int& gpId = gp_id[pp];			// 這個人所屬團體
				int& gpFn = gp_fn[gpId];		// 隊伍中這個人所屬團體的最後一個人的id

				int& pp_nt   = nextId[pp];		// 這個新人後面排的人
				int& gpFn_nt = nextId[gpFn];	// 自己團最後一個人的下一個人
				// ------------------------------------------------------
				

				// 沒人在排隊
				if (fst == -1) {
					fst = lst = pp; // 總隊伍頭尾都是自己
					if (gpId) { // 有所屬團體
						gpFn = pp; // 隊伍中的這團只有他個就在尾端他就最後一個
					}
					pp_nt = -1; // 他後面沒人

				// 有自己人在排隊且自己人在前面 --> 可以插隊
				} else if (gpFn != -1 && gpFn != lst) {
					pp_nt = gpFn_nt;	// 插隊1::自己的後面 = 自己團最後一個人的下一個人
					gpFn_nt = pp;		// 插隊2::排到自己團的最後一個人後
					gpFn = pp;			// 自己是這團的最後一個人

				// 沒自己人在排隊或自己人就在後面 --> 乖乖排隊
				} else {
					nextId[lst] = pp;	// 標記最後一個人的後面是這個新人
					lst = pp;			// 新人加入隊伍最後一個
					if (gpId)
						gpFn = pp;  // 獨行俠 -> 建立隊伍(最後就是自己)
					pp_nt = -1;			// 這個新人後面沒人了
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