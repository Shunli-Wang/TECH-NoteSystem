// https://leetcode.cn/problems/reverse-pairs/
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int merge(vector<int>& arr, vector<int>& help, int l, int m, int r) {
        // 计算翻转对数量
        // [10 20 30 40]  [1 1 20 20]
        //   j            m+1  k
        int k = m+1;
        int ans = 0;
        for (int j = l; j <= m; j++) { // j不回退，每次清算j位置的数字
            while (k <= r && (long) arr[j] > 2*(long) arr[k]) { // 注意2*int的溢出情况
                k++; // 若右侧有k满足，则一直++，直到不满足，推到k的右边界
            }
            ans += k-(m+1);
        }

        // sort
        int a = l, b = m+1, i=l;
        while (a <= m && b <= r) {
            help[i++] = arr[a] < arr[b] ? arr[a++] : arr[b++];
        }
        while (a <= m) {
            help[i++] = arr[a++];
        }
        while (b <= r) {
            help[i++] = arr[b++];
        }
        for (i = l; i <= r; i++) {
            arr[i] = help[i];
        }

        return ans;
    }

    int mergeSort(vector<int>& arr, vector<int>& help, int l, int r) {
        if (l == r) {
            return 0;
        }
        int m = l + ((r-l)>>1);
        return mergeSort(arr, help, l, m) + mergeSort(arr, help, m+1, r) + merge(arr, help, l, m, r);
    }

    int reversePairs(vector<int>& nums) {
        int len = nums.size();
        vector<int> help(len, 0);
        return mergeSort(nums, help, 0, len-1);
    }
};