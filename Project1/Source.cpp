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

	int n, k, tmp, t = 1;
	while (scanf("%d", &n) != EOF) {
		printf("Line #%d\n", t); t++;
		int fst, lst;
		fst = lst = -1;
		fill(HK, HK + N, 0);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &k);
			for (int j = 0; j < k; j++) {
				scanf("%d", &tmp);
				HK[tmp] = i;
			}
		}
		fill(L, L + N, -1);
		fill(K, K + 1001, -1);
		char c[20];
		while (scanf("%s", c)) {
			if (c[0] == 'E') {
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
			} else if (c[0] == 'D') {
				if (fst == K[HK[fst]])K[HK[fst]] = -1;
				printf("%d\n", fst);
				fst = L[fst];
			} else if (c[0] == 'S')break;
			//PP(fst);
		}
	}
	//system("pause");
	return 0;
}