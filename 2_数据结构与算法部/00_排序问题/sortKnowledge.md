
# 选择排序
从0到N-1找到最小的元素，和idx=0元素交换；
从1到N-1找到最小的元素，和idx=1元素交换；
...
idx和N-1相同时达到最后一个元素，结束。

```c++
void selectionSort(vector<int> arr) {
    if (arr == NULL || arr.size()<2) return; // 特殊情况过滤
    for (int i=0; i<arr.size()-1; i++) { // 外围循环控制搜索范围
        int minIdx = i; // 最小元素位置
        for (int j=i+1; j<arr.size(); j++) {
            minIdx = arr[j] < arr[minIdx] ? j : minIdx; // 锁定最小元素下标
        }
        swap(arr[i], arr[minIdx]);
    }
}
```

# 冒泡排序
idx=0开始到N-2从左到右依次两两比较，如右侧小则交换位置，第一轮结束之后最大值放置于N-1；
idx=0开始到N-3重复；

0,1,2,..,n-3,n-2,n-1
```c++
void bobalSort(vector<int> arr) {
    for (int i=arr.size()-1; i>=0; i--) { // 此轮目标是放好i位置
        for (int j=0; j<i; j++) { // 比较左位置
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}
```

# 插入排序
实现idx=0到idx=0上有序，默认完成。
实现idx=0到idx=1上有序，idx=1元素向前比较移动，直到不逆序或到达边界。

```c++
void insertionSort(vector<int> arr){
    for (int i=1; i<arr.size(); i++) {
        int j = i;
        while (j>0 && arr[j-1]>arr[j]) {
            swap(arr[j-1], arr[j]);
            j--;
        }
    }
}
```

# 归并排序-MergeSort
左部分有序，右部分有序，利用merge过程让左右整体有序。
merge过程: 谁小拷贝谁，直到左右两部分的数字耗尽，拷贝回原数组。

复杂度O(N*logN),因为没有浪费比较行为。比O(N^2)要快很多。
利用归并排序的便利性可以解决很多问题 - 归并分治类问题。
冯诺依曼发明的算法。

912.排序

```c++
// [1,2,3] [2,3,4]
//  l   m  m+1  r
//  a       b
void merge(vector<int>& arr, vector<int>& help, int l, int m, int r){
    int i = l; // 外数组索引
    int a = l;
    int b = m+1;
    while (a <= m && b <= r) { // 还没有到头
        help[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++]; // 谁小先拷贝谁
    }
    while (a <= m) { // a还没到头，全部拷贝
        help[i++] = arr[a++];
    }
    while (b <= r) { // b还没到头，全部拷贝
        help[i++] = arr[b++];
    }
    for (i=l; i<=r; i++) { // 拷贝回去
        arr[i] = help[i];
    }
}

void process(vector<int>& arr, vector<int>& help, int l, int r){
    if (l == r) {
        return;
    }
    int m = l + ((r-l)>>1); // 位运算一定用括号进行特殊处理，否则优先级会出问题
    process(arr, help, l, m); // 左范围[l...m]有序
    process(arr, help, m+1, r); // 右范围[m+1...r]有序
    merge(arr, help, l, m, r); // 整体范围有序
}

void mergeSort(vector<int>& arr){
    int len = arr.size();
    vector<int> help(len, 0);
    process(arr, help, 0, len-1); // 闭区间
}
```

# 归并分治
1. 思考一个问题在大范围上的答案，是否等于，左部分的答案 + 右部分的答案 + 跨越左右产生的答案。
2. 计算“跨越左右生成的答案”时，如果加上左右各自`有序`的设定，会不会获得`计算的便利性`。
3. 如果以上两点都成立，那么很可能被`归并分治`解决
4. 求解答案过程中只需要加入归并排序的过程即可，因为要让左右各自有序，获得计算便利性。

精妙又美丽的思想传统：只有具备了很多的思想传统，才能想出来。所以前期有“被架空、怎么想出来”的思想很正常，一定坚持下去，不然会错过很多精妙的思想。

`参考题目：小和问题、逆序对数量`

# 快速排序-QuickSort
在[l,,,r]范围内随机选择一个数值arr[randIdx]=k，通过k进行荷兰国旗问题划分为三个区域[<k][==k][>k]，之后返回[==k]的左右边界继续进行划分。

```c++
// [3 2 4 1 5 5 5 9 7 8 6]
//  l       l   r i     r
//          l   r i      
//  i
pair<int, int> partition(vector<int>& arr, int l, int r, int k) {
    int i = l;
    while (i <= r) { // 注意这里是单分支的情况，不是多分支
        if (arr[i] < k) {
            swap(arr[l++], arr[i++]); // 出现小值 交换后，一同增长
        } else if (arr[i] == k) {
            i++; // 出现等值 i增长
        } else if (arr[i] > k) {
            swap(arr[i], arr[r--]); // 出现大值 交换后，i不变
        }
    }
    return pair<int, int> (l, r);
}

void quickSort(vector<int>& arr, int l, int r) {
    if (l >= r) { // 防止rl的情况发生，导致无法取随机数
        return;
    }
    int randIdx = l + rand() % (r-l+1);
    int k = arr[randIdx]; // 随机挑一个数字
    pair<int, int> l_r = partition(arr, l, r, k);
    quickSort(arr, l, l_r.first-1);
    quickSort(arr, l_r.second+1, r);
}

vector<int> sortArray(vector<int>& arr) {
    int len = arr.size();
    quickSort(arr, 0, len - 1);
    return arr;
}
```

# 堆结构
数组从0开始到s-1一共s个元素看为是一个堆，左孩子下标`2*i+1`若越界则无；右孩子`2*i+2`若越界则无；父节点`(2-1)/2`。

HeapInsert：每次在数组末尾[s]位置添加新元素，进行实时调整保证大跟堆。往上走因为只有一个父节点，所以比较好写。
```c++
void heapInsert(vector<int> arr, int idx) { // 因为是将一个元素往前放，所以无需s
    while (arr[idx] > arr[(idx - 1) / 2]) { // 此节点大于了自己的父节点，向上调整
        swap(arr[idx], arr[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}
```

Heapify: 返回大根堆的堆顶并移除，调整堆结构保证是大根堆。往下走因为涉及到左右孩子的max比较选下标，所以比较复杂。
```c++
void heapify(vector<int>& arr, int idx, int s) {
    int l_c = 2 * idx + 1; // 左孩子
    while (l_c < s) { // 若存在左孩子
        // 挑选左右孩子中最大的下标
        int max_c = (l_c+1) < s && arr[l_c+1] > arr[l_c] ? l_c+1 : l_c;
        if (arr[max_c] > arr[idx]) { // 若存在子比父大情况，则进行交换，idx和l_c进行更新。
            swap(arr[max_c], arr[idx]);
            idx = max_c;
            l_c = 2 * idx + 1;
        } else {
            break;
        }
    }
}
```

优良特性：支持用户随意修改有校区中的数值，变大则向上经历heapInsert，变小则向下经历heapify。

# 堆排序-HeapSort

```c++
void heapSort(vector<int>& arr) {
    for (int i=0; i<arr.size(); i++) { // 动态维护一个大根堆
        heapInsert(arr, i);
    }
    for (int i=0; i<arr.size(); i++) {
        swap(arr[0], arr[arr.size()-1-i]); // 当前堆顶放在最后一个位置
        heapify(arr, 0, arr.size()-1-i); // 0位置元素向下进行heapify
    }
}
```
