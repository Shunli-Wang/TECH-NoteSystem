#include<iostream>
#include<vector>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> row1(n, 0);
    for (int i=0; i<n; i++) cin >> row1[i];
    vector<int> row2(n, 0);
    for (int i=0; i<n; i++) cin >> row2[i];

    // 计算前缀和
    for (int i=n-2; i>=0; i--) {
        row1[i] = row1[i] + row1[i+1];
    }
    for (int j=1; j<n; j++) {
        row2[j] = row2[j] + row2[j-1];
    }

    int ans = 0;

    // 枚举各种拐弯情况
    for (int i=0; i<n; i++) {
        if (i == 0) {
            ans = max(ans, row1[i+1]);
        } else if (i == (n-1)) {
            ans = max(ans, row2[n-2]);
        } else {
            ans = max(ans, max(row1[i+1], row2[n-2]));
        }
    }

    cout << ans;

    return 0;
}

// A先走，B后走，只能朝右侧和下侧移动
// B吃到的最大糖果数量



