#include<iostream>
#include<vector>
using namespace std;

int main() {
    int n, sn;
    cin >> n;
    vector<int> nums(n, 0);
    for (int i=0; i<n; i++) {
        cin >> nums[i];
    }
    cin >> sn;

    int minIdx = 0, max = nums[0];
    for (int i=0; i<n; i++) {
        if (nums[i] < minIdx) {
            minIdx = i; // 找到最小值的下标minIdx
        }
    }

    int s = -1, e = -1;
    for (int i=0; i<n; i++) {
        int index = (minIdx + i) % n; // 主要是这个循环语句
        if (nums[index] == sn) {
            if (s == -1) {
                s = index;
                e = index;
            } else {
                e = index;
            }
        }
    }

    cout << s << " " << e << endl;
}


