#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/* 并查集实现:还是有很多的细节坑 */
int MAXN = 301;
int* father = new int[MAXN];

void build(int n) {
    for (int i=1; i<=n; i++) {
        father[i] = i;
    }
}

int find(int x) {
    if (x != father[x]) {
        father[x] = find(father[x]);
    }
    return father[x];
}

bool unionSet(int a, int b) {
    int fa = find(a); // !!! 这里是find，不是father
    int fb = find(b);
    if (fa != fb) {
        father[fa] = fb; // 不在同一个集合中，此时操纵的是father节点，而不是原始节点!
        return true;
    } else {
        return false; // 在同一个集合中，返回false，不做任何操作
    }
}

/* 比较器实现，增序 */
struct cmp{
    bool operator()(vector<int>& a, vector<int>& b) {
        return a[2] < b[2]; // 小于是true，保留不进行交换
    }
};

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> edges(m);

    for (int i=0; i<m; i++) {
        int a, b, val;
        cin >> a >> b >> val;
        edges[i] = {a, b, val};
    }

    build(n); // 建立并查集

    sort(edges.begin(), edges.end(), cmp());

    int ans = 0; // 存放结果权重和
    int cnt = 0; // 存放边的数量

    for (auto edge : edges) {
        if (unionSet(edge[0], edge[1])) {
            // 不在同一个集合中，而且已经进行了合并
            ans += edge[2];
            cnt++;
        }
        // 端点已经在一个集合中，跳过
    }

    if (cnt == n-1) {
        cout << ans << endl;
    } else {
        cout << cnt << " " << ans << "not fully connected graph!" << endl;
    }

    return 0;
}


// 点的编号从1开始，到n
// 4 5
// 1 2 10
// 3 4 50
// 4 1 20

