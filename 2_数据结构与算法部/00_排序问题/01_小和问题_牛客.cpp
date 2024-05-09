// https://www.nowcoder.com/practice/edfe05a1d45c4ea89101d936cac32469
#include <iostream>
#include <vector>
using namespace std;

long merge(vector<int>& arr, vector<int>& help, int l, int m, int r) {
    // 计算所有两侧有序数组的小和
    // [1 2 3 4]  [2 5 6 7]
    //      j      k       
    // [0 0 0 0]  [2 5 6 7] 极端情况
    //      j      k  
    int j = l;
    long allSum = 0;
    long cur = 0;
    for (int k = m+1; k<=r; k++) { // k不回退
        while (j <= m && arr[j] <= arr[k]) { // j也不回退,j不能跨过m
            cur += arr[j++];
        }
        allSum += cur;
    }

    // 正常的归并排序
    int a = l;
    int b = m+1;
    int i = l;
    while (a<=m && b<=r) {help[i++] = arr[a] < arr[b] ? arr[a++] : arr[b++];}
    while (a<=m) {help[i++] = arr[a++];}
    while (b<=r) {help[i++] = arr[b++];}
    for (i=l; i<=r; i++) {arr[i] = help[i];}

    return allSum;
}

long mergeSort(vector<int>& arr, vector<int>& help, int l, int r) {
    if (l == r) {
        return 0;
    }
    int m = l + ((r-l)>>1);
    return mergeSort(arr, help, l, m) + 
           mergeSort(arr, help, m+1, r) + 
           merge(arr, help, l, m, r);
}

long getSum(vector<int>& arr, int len) {
    vector<int> help(len, 0);
    return mergeSort(arr, help, 0, len-1);
}

int main() {
    int len, temp;
    cin >> len;
    vector<int> arr;
    for (int i=0; i<len; i++) {
        cin >> temp;
        arr.push_back(temp);
    }

    long res = getSum(arr, len);
    printf("%lld", res); // 笔试中有可能会出现int溢出，所以最好选择long类型
}
// 64 位输出请用 printf("%lld")

// 1. 小和问题使用了MergeSort的变种
// 2. 这么多数字相加可能会有溢出，所以应该使用long类型存储
// 3. 最难想的部分在merge之前的小和计算，j和k指针都不会回退，会累积求和

