// https://www.nowcoder.com/practice/1ae8d0b6bb4e4bcdbf64ec491f63fc37
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(vector<int>& a, vector<int>& b){
    return a[0] < b[0]; // 小于就是1，不用交换。最后从小到大。
}

struct cmp{
    bool operator()(vector<int>& a, vector<int>& b){
        return a[0] < b[0]; // 小于就是1，不用交换。最后从小到大。
    }
};

struct queCmp{
    bool operator()(int& a, int& b){
        return a > b; // 小于就是1，不用交换。最后从小到大。
    }
};

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

    // 创建小根堆（系统默认是大根堆）
    priority_queue<int, vector<int>, queCmp> heap; // 默认less是大根堆，此处用小根堆greater<int>

    int cnt = 0, maxCnt = 0;
    for (int i=0; i<len; i++) {
        while ((!heap.empty()) && heap.top() <= list[i][0]) { // 1. 弹出所有大于此线段起始[0]的堆顶元素，即不在统计范围内的线段
            heap.pop();
        }
        heap.push(list[i][1]); // 2. 结束位置[1]入堆
        cnt = heap.size(); // 3. 计算堆的大小，冲进[0]位置的线段数量
        maxCnt = max(maxCnt, cnt); // 获取max值
    }
    cout << maxCnt << endl;
}

// 优先级队列比较器使用方法
// priority_queue<int, vector<int>, greater<int>> heap; 
// 默认：  less        大根堆      a<b  按道理是123，小在前，但是逆序后大在前
//        greater     小根堆      a>b  按道理是321，大在前，但是逆序后小在前
// 参数传入：传入类型所有是queCmp

// sort传入实例所以是cmp()


// 题解（最好画图理解下，和单调栈有点像）
// 1. 按照线段开头位置按升序进行排序；
// 2. 维护一个小根堆，存放后续线段结尾的位置；
// 3. 对于一个新的线段[x, y]，将小根堆内<=x的元素全部弹出，让弹出的线段失效；并且把自己的结尾处加入到小根堆内；进行数量结算（此时结算的是所有能够冲进x边界内线段的数量）；
// 4. 每个线段统计数量，取max即可；


