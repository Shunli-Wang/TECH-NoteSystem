#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int n; cin >> n;
    int start; cin >> start;
    int target; cin >> target;
    vector<int> arr(n, 0);
    for (int i=0; i<n; i++) cin >> arr[i];

    sort(arr.begin(), arr.end()); // 从小到大排序
    int ans = 0;

    while (true) {
        for (int i=0, j=n-1; i < j; ans++) { // 双指针移动，ij开区间定范围
            if (start >= arr[i]) {
                start++;
                i++;
                if (start == target) return ans;
            } else {
                start--;
                j--;
            }
        }
    }

    cout << ans;

    return 0;
}

// 贪心：每次都取最好的，直到到达目标。

// 小明参加一个在线比赛。需要与n个对手对战。当小明的等级大于等于对手的等级，他就能赢。如果小明赢了，等级提升1级，
// 否则会减少1级。对手的等级固定不变。小明的初始等级是x，小明想把他的等级提高到y（y>x）。

// 输入：7 2 10
//      3 1 9 2 5 20 8
// 输出：20