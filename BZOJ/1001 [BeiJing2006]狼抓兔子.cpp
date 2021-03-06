#include <bits/stdc++.h>
using namespace std;

typedef int Flow_Type;

const Flow_Type INF = 0x3f3f3f3f;
const int N = 1000006;

struct Edge;

int level[N];
int head[N];

struct Edge {
	Flow_Type capacity, flow;
	int to, next;
} e[6 * N];

bool levelGraph(int s, int t) {
	memset(level, 0, sizeof level);
	queue<int> bfs;
	bfs.push(s);
	level[s] = 1;
	while (!bfs.empty()) {
		int pos = bfs.front(); bfs.pop();
		for (int i = head[pos]; i; i = e[i].next) {
			if (e[i].flow < e[i].capacity && !level[e[i].to]) {
				level[e[i].to] = level[pos] + 1;
				if (e[i].to == t) return true;
				else bfs.push(e[i].to);
			}
		}
	}
	return false;
}

Flow_Type findPath(int s, int t, Flow_Type flow) {
	if (s == t) return flow;
	Flow_Type ret = 0;
	for (int i = head[s]; ret < flow && i; i = e[i].next) {
		if (level[s] + 1 == level[e[i].to] && e[i].flow < e[i].capacity) {
			Flow_Type tmp = findPath(e[i].to, t, min(e[i].capacity - e[i].flow, flow));
			ret += tmp;
			flow -= tmp;
			e[i].flow += tmp;
			e[i ^ 1].flow -= tmp;
		}
	}
	if (!ret) level[s] = -1;
	return ret;
}

Flow_Type dinic(int s, int t) {
	Flow_Type ans = 0;
	while (levelGraph(s, t)) {
		ans += findPath(s, t, INF);
	}
	return ans;
}

int cnt = 1;

void addEdge(int from, int to, int capacity) {
	e[++cnt].to = to; e[cnt].next = head[from]; e[cnt].capacity = capacity; head[from] = cnt;
	e[++cnt].to = from; e[cnt].next = head[to]; e[cnt].capacity = capacity; head[to] = cnt;
}

int n, m, x, u;

int main() {
	scanf("%d%d", &n, &m);
	if (n == 1 && m == 1) return puts("2147483647"), 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m; j++) {
			scanf("%d", &x);
			u = (i - 1) * m + j;
			addEdge(u, u + 1, x);
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &x);
			u = (i - 1) * m + j;
			addEdge(u, u + m, x);
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			scanf("%d", &x);
			u = (i - 1) * m + j;
			addEdge(u, u + m + 1, x);
		}
	}
	printf("%d", dinic(1, n * m));
}