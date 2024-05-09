// https://leetcode.cn/problems/kth-largest-element-in-an-array/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
public:
    int ans = 0;
    int desPos = 0;
    // [2 3 1 4 5 5 5 8 9 6 7]
    //  l                   r
    //  i 
    //          l   r
    pair<int, int> partition(vector<int>& arr, int l, int r, int k) {
        int i = l;
        while (i <= r) {
            if (arr[i] < k) {
                swap(arr[i++], arr[l++]);
            } else if (arr[i] == k) {
                i++;
            } else if (arr[i] > k) {
                swap(arr[i], arr[r--]);
            }
        }
        return pair<int, int> (l, r);
    }

    // 改进快排版（会碰到[1]的坑）
    void quickSort(vector<int>& arr, int l, int r) {
        if (l >= r) { // 左右指针撞到一起的时候，卡到了k的位置，刚好可以处理[1]这种情况
            ans = arr[l];
            return ;
        }
        int k = arr[l + rand() % (r-l+1)];
        pair<int, int> res = partition(arr, l, r, k); // 荷兰国旗划分，对k元素进行定位
        if (res.first <= desPos && desPos <= res.second) { // 等于区域压中结果，返回数值
            ans = k; // 位于区间范围内时，卡到了k的位置
            return ;
        } else if (desPos > res.second) {
            quickSort(arr, res.second + 1, r);
        } else if (desPos < res.first) {
            quickSort(arr, l, res.first - 1);
        }
    }

    // for循环配合partition实现，简洁易懂
    void randomizedSelect(vector<int>& arr, int l, int r) {
        while (l <= r) {
            int k = arr[l + rand() % (r-l+1)];
            pair<int, int> res = partition(arr, l, r, k);
            if (res.first <= desPos && desPos <= res.second) { // 等于区域压中结果，返回数值
                ans = k;
                return ;
            } else if (desPos > res.second) {
                l = res.second + 1;
            } else if (desPos < res.first) {
                r = res.first - 1;
            }
        }
    }

    int findKthLargest(vector<int>& nums, int k) {
        desPos = nums.size() - k; // 从小到大进行排列，是去求第len-k个最小的元素
        quickSort(nums, 0, nums.size()-1);
        randomizedSelect(nums, 0, nums.size()-1);
        return ans;
    }

    // 基于大根堆实现，O(N*logN)
    int findKthLargestHeap(vector<int>& nums, int k) {
        // priority_queue<int> heap; // 大根堆
        priority_queue<int, vector<int>, less<int>> heap; // 默认less: a<b 大根堆，优先队列队首指向最后，队尾指向最前面的缘故
        // priority_queue<int, vector<int>, greater<int>> heap; // greater: a>b 小根堆
        for (int num : nums) {
            heap.push(num);
        }
        for (int i=0; i<(k-1); i++) {
            heap.pop();
        }
        return heap.top();
    }
};

// 1. 妙啊，快排的本质就是partition过程，划分[<x][==x][>x]三个区域，所以天然可以二分求k个最大元素这种问题
// 