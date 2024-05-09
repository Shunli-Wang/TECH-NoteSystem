#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// 创建小根堆
int* heap = new int[10001];
int s = 0;

struct cmp{
    bool operator()(vector<int>& a, vector<int>& b){
        return a[0] < b[0]; // 小于就是1，不用交换。最后从小到大。
    }
};

void heapInsert(int* arr, int idx) { // 往上走, 小根堆是目标
    while (arr[idx] < arr[(idx - 1) / 2]) { // 如果小于自己的父
        swap(arr[idx], arr[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

void heapify(int* arr, int idx, int s) { // 往下走, 小根堆是目标
    int l_c = 2 * idx + 1;
    while (l_c < s) {
        int min_c = l_c + 1 < s && arr[l_c + 1] < arr[l_c] ? l_c + 1 : l_c; // 挑选较小的
        if (arr[min_c] < arr[idx]) {
            swap(arr[min_c], arr[idx]);
            idx = min_c;
            l_c = 2 * idx + 1;
        } else break;
    }
}

int main() {
    int len;
    cin >> len;
    vector<vector<int>> list;

    int temp;
    vector<int> tempList;
    for (int i=0; i<len; i++) {
        tempList.clear();
        cin >> temp;
        tempList.push_back(temp);
        cin >> temp;
        tempList.push_back(temp);
        list.push_back(tempList);
    }

    // 按照起始位置进行排序
    sort(list.begin(), list.end(), cmp()); // 从小到大排列 return a<b;

    int cnt = 0, maxCnt = 0;
    for (int i=0; i<len; i++) {
        // cout << list[i][0] << endl;
        while (s > 0 && heap[0] <= list[i][0]) { // 1. 弹出所有大于此线段起始[0]的堆顶元素，即不在统计范围内的线段
            swap(heap[0], heap[--s]); // 将最后一个元素和堆顶互换，再进行heapify
            heapify(heap, 0, s);
        }
        heap[s] = list[i][1];
        heapInsert(heap, s++); // 2. 结束位置[1]入堆
        cnt = s; // 3. 计算堆的大小，冲进[0]位置的线段数量
        maxCnt = max(maxCnt, cnt); // 获取max值
    }
    cout << maxCnt << endl;
}

// 64 位输出请用 printf("%lld")
