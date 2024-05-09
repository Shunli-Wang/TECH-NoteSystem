#include<iostream>
#include<vector>
using namespace std;

int mainMatrix() {
    // 点的最大数量
    int MAXN = 11;

    // 邻接矩阵建图，按照MAXN*MAXN建，并且清空
    int** graph1 = new int*[MAXN];
    for (int i=0; i<MAXN; i++) {
        graph1[i] = new int[MAXN]();
    }
    for (int i=0; i<MAXN; i++) { 
        for (int j=0; j<MAXN; j++) {
            graph1[i][j] = 0; // 全部置零，表示无路径相连
        }
    }

    // 输入点的数量
    int n, m; cin >> n >> m; // 点的数量从1~n，建图下标从0开始，会浪费初始位置
    // 输入图信息，外部录入[s, e, w]
    vector<vector<int>> edges;
    for (int i=0; i<m; i++) {
        int s, e, w;
        cin >> s >> e >> w;
        edges.push_back(vector<int>{s, e, w});
    }

    // 建立有向带权图
    for (auto edge : edges) {
        graph1[edge[0]][edge[1]] = edge[2];
    }

    // 建立无向带权图
    for (auto edge : edges) {
        graph1[edge[0]][edge[1]] = edge[2];
        graph1[edge[1]][edge[0]] = edge[2]; // 对称建图
    }

    // 邻接矩阵遍历图
    for (int i=0; i<=n; i++) {
        for (int j=0; j<=n; j++) {
            cout << graph1[i][j] << " " << endl;
        }
    }

    return 0;
}

// 邻接表：有权图
int main() { // mainTable
    // 输入数据处理
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> edges(n+1); // n个节点的信息，所以是有n+1个容器

    // 输入边的信息
    for (int i=0; i<m; i++) {
        int s, e, w;
        cin >> s >> e >> w; // s有e这个邻居，可以塞进去 
        edges[s].push_back({e, w});
    }

    // 邻接表遍历图
    cout << endl;
    for (int i=1; i<=n; i++) {
        for (auto edge : edges[i]) {
            cout << i << " " << edge.first << " " << edge.second << endl;
        }
    }

    return 0;
}


