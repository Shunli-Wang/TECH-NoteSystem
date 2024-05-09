#include<iostream>
#include<stack>
#include<vector>
using namespace std;

int main() {
    // 数据输入
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    for (int i=0; i<n; i++) {cin >> arr[i];}

    // 单调栈构建
    stack<int> stk;
    vector<int> left(n, 0);
    vector<int> right(n, 0);

    // 入栈
    for (int i=0; i<n; i++) {
        while (!stk.empty() && arr[stk.top()] <= arr[i]) {
            int idx = stk.top(); stk.pop();
            left[idx] = stk.empty() ? -1 : stk.top();
            right[idx] = i;
        }
    }

    // 结算
    while (!stk.empty()) {
        int idx = stk.top(); stk.pop();
        left[idx] = stk.empty() ? -1 : stk.top();
        right[idx] = -1;
    }

    // 相同值矫正
    for (int i=n-1; i>=0; i--) {
        if (right[i] != -1 && arr[i] == arr[right[i]]) {
            right[i] = right[right[i]];
        }
    }

    // 计算最终结果
    for (int i=0; i<n; i++) {
        if (right[i] == -1) {
            right[i] = 0;
        } else {
            right[i] = right[i] - i;
        }
        cout << right[i] << " ";
    }

    return 0;
}
