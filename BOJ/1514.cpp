#include <cstdio>
#include <queue>
#include <string.h>
int pre[10][10][10];
int can[][3]{
	{ 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 },
		{ 2, 0, 0 }, { 0, 2, 0 }, { 0, 0, 2 },
		{ 3, 0, 0 }, { 0, 3, 0 }, { 0, 0, 3 },

		{ 1, 1, 0 }, { 0, 1, 1 }, { 2, 2, 0 }, 
		{ 0, 2, 2 }, { 3, 3, 0 }, { 0, 3, 3 },

		{ 1, 1, 1 }, { 2, 2, 2 }, { 3, 3, 3 }
};
void make(){
	struct node{
		int n[3];
		int c;
	};
	std::queue<node> q;
	memset(pre, 0xff, sizeof(pre));
	q.push({ { 0, 0, 0 }, 0 });
	while (!q.empty()){
		auto t = q.front();
		q.pop();
		if (pre[t.n[0]][t.n[1]][t.n[2]] != -1) continue;
		pre[t.n[0]][t.n[1]][t.n[2]] = t.c;
		for (int i = 0; i < 18; i++){
			int nu[3] = { t.n[0] + can[i][0], t.n[1] + can[i][1], t.n[2]+can[i][2] };
			int mnu[3] = { t.n[0] - can[i][0], t.n[1] - can[i][1], t.n[2]-can[i][2] };
			for (int j = 0; j < 3; j++){
				nu[j] = (nu[j] + 10) % 10;
				mnu[j] = (mnu[j] + 10) % 10;
			}
			if (pre[nu[0]][nu[1]][nu[2]] == -1) q.push({ { nu[0], nu[1], nu[2] }, t.c + 1 });
			if (pre[mnu[0]][mnu[1]][mnu[2]] == -1) q.push({ { mnu[0], mnu[1], mnu[2] }, t.c + 1 });
		}
	}
}
char str1[110], str2[110];
int dy[110][10][10];
int main(void){
	make();
	int n;
	scanf("%d%s%s", &n, str1+2, str2+2);
	for (int i = 2; i < n+2; i++) str1[i] -= '0';
	for (int i = 2; i < n+2; i++) str2[i] -= '0';

	for (int idx = 2; idx < n+2; idx++){
		for (int i = 0; i < 10; i++) for (int j = 0; j < 10; j++) dy[idx][i][j] = 0x7fffff;
		for (int n1 = 0; n1 < 10; n1++){
			for (int n2 = 0; n2 < 10; n2++){
				for (int t1 = 0; t1 < 10; t1++){
					for (int t2 = 0; t2 < 10; t2++){
						int d[] = { n1 - str2[idx-2], n2 - t1, str1[idx] - t2};
						for (int i = 0; i < 3; i++) d[i] = (d[i] + 10) % 10;
						dy[idx][t1][t2] = std::min(dy[idx][t1][t2], dy[idx - 1][n1][n2] + pre[d[0]][d[1]][d[2]]);
					}
				}
			}
		}
	}
	printf("%d", dy[n + 1][str2[n]][str2[n + 1]]);
}
