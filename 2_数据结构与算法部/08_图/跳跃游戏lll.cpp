#include<iostream>
#include<vector>
using namespace std;

// s和e都是从1开始
int jump(int N, int s, int e, vector<int> arr) {
    vector<bool> walk(arr.size(), false);
    int ans = process(arr, e, s, walk);
    return ans == INT32_MAX ? -1 : ans;
}

// 递归含义 从i到e最少需要几步
// work[i] == false 之前没到过
int process(vector<int> arr, int e, int i, vector<bool>& walk) {
    if (i < 1 || i > arr.size()) return INT32_MAX;
    if (walk[i-1]) return INT32_MAX; // 之前走过，不要走了
    if (i == e) return 0;
    // 第一次来到i
    walk[i-1] = true;
    int p1 = i - arr[i - 1];
    int p2 = i + arr[i - 1];
    int ans = INT32_MAX;
    ans = min(ans, process(arr, e, p1, walk));
    ans = min(ans, process(arr, e, p2, walk));
    walk[i-1] = false; // 引用传递需要恢复现场
    return ans + (ans == INT32_MAX ? 0 : 1);
}
