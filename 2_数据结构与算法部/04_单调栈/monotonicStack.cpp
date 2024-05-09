#include<iostream>
#include<vector>
#include<stack>
using namespace std;
// 输入：
// 7
// 3 4 1 5 6 2 7

// 不含有重复值，返回i位置数字，左侧右侧、临近、最小位置
void main () {
    // 处理输入
    int n = 0; cin >> n;
    vector<int> arr;
    for (int i=0; i<n; i++) { int temp; cin >> temp; vec.push_back(temp); }

    // 创建输出
    vector<int> left(n, 0), right(n, 0);
    stack<int> stk;

    // 1阶段：循环遍历
    for (int i=0; i<n; i++) {
        // (栈非空 && cur值出现小压大) 生成结果记录
        while (!stk.empty() && arr[stk.top()] >= arr[i]) { // 写大小的顺序还是按照纸上的左右，等于则过早结算，栈内无重复值
            int index = stk.top(); stk.pop(); // 弹栈，生成记录
            right[index] = i; // 右侧一定是i
            left[index] = stk.empty() ? -1 : stk.top(); // 左侧需判定
        }
        // (栈空 || 正常大压小情况) 直接压栈
        stk.push(i);
    }

    // 2阶段：清算阶段
    while (!stk.empty()) {
        int index = stk.top(); stk.pop(); // 弹栈，生成记录
        right[index] = -1; // 右侧一定是-1
        left[index] = stk.empty() ? -1 : stk.top(); // 左侧需判定
    }

    // 3阶段：逆向修正
    for (int i=n-1; i>=0; i--) { // 判断出栈条件中过早结算
        // (此结果非-1 && 跳跃过程出现重复情况)
        if (right[i]!=-1 && arr[i] == arr[right[i]]) {
            right[i] = right[right[i]];
        }
    }

    for (int i=0; i<n; i++) {
        cout << left[i] << right[i] << endl;
    }
}

// 生成记录的过程有点“三连”的感觉，记录、左、右
// 两个while，一个for，核心判断等号特殊考虑

// 特殊下标处理：左填-1，右侧填len和-1要具体讨论，看题目求什么
// 特殊下标处理：本质上默认arr[-1]=-00; arr[len]=-00
// 条件位置：一定是栈顶元素在前，好分析

void practice() { // 左右侧\最近的\比他小的
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    for (int i=0; i<n; i++) {cin >> arr[i];}

    // 创建单调栈内容
    stack<int> stk;
    vector<int> left(n, 0), right(n, 0);

    // 1遍历
    for (int i=0; i<n; i++) {
        while (!stk.empty() && arr[stk.top()] >= arr[i]) { // 触发弹栈条件，过早结算，栈内不允许有重复值
            int idx = stk.top(); stk.pop(); 
            left[idx] = stk.empty() ? -1 : stk.top();
            right[idx] = i;
        }
        stk.push(i);
    }

    // 2清算
    while (!stk.empty()) {
        int idx = stk.top(); stk.pop(); 
        left[idx] = stk.empty() ? -1 : stk.top();
        right[idx] = -1;
    }

    // 3修正过早结算节点
    for (int i=n-2; i>=0; i--) { // 这个地方卡住了，画错内容
        if (right[i] != -1 && arr[i] == arr[right[i]]) {
            right[i] == right[right[i]];
        }
    }
}


// 962.最大坡宽度
// 316.去除重复字母

