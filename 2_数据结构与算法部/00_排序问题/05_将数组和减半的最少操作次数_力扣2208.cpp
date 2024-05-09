#include<iostream>
#include<queue>
#include<vector>
using namespace std;

class Solution {
public:
    /* 经典堆 */
    int halveArray(vector<int>& nums) {
        double sum = 0;
        priority_queue<double, vector<double>, less<double>> heap; // 大根堆
        for (int num : nums) {
            heap.push((double) num);
            sum += (double) num;
        }
        sum = sum / 2;

        int ans = 0;
        double cur = 0;
        while (cur < sum) { // 弹出最大，除以二再放回去
            double temp = heap.top(); heap.pop();
            temp = temp / 2;
            heap.push(temp);
            cur += temp;
            ans++;
        }
        return ans;
    }

    /* 位运算版本 */
    int halveArray(vector<int>& nums) {
        long sum = 0;
        priority_queue<long> heap;
        for (int num : nums) {
            heap.push(((long) num) << 20); // 左移20次不会改变最后的结果
            sum += ((long) num) << 20;
        }
        sum = sum / 2;

        int ans = 0;
        long cur = 0;
        while (cur < sum) {
            long temp = heap.top(); heap.pop();
            temp = temp / 2;
            heap.push(temp);
            cur += temp;
            ans++;
        }
        return ans;
    }
};
