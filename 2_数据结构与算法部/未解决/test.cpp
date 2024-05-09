
// 当前位置cur
// 还有rest步需要走
// 目标是aim
// 有哪些位置N
int process(int cur, int rest, int aim, int N) {
    if (rest == 0) { // 不需要走了，走完了
        return cur == aim ? 1 : 0; // 如果在位置上面，就是1，否则是0
    }
    /* 底层逻辑是在这里罗列可能性 */
    // 还有步数要走,要按照规则走，进行罗列
    if (cur == 1) {
        return process(2, rest-1, aim, N); // 得先去看看2位置能不能走成功
    }
    if (cur == N) {
        return process(N-1, rest-1, aim, N);
    }
    // 停在中间位置
    return process(cur+1, rest-1, aim, N) + process(cur-1, rest-1, aim, N);
}

// 先手函数，获得最好的分数
int f(vector<int> arr, int L, int R) {
    if (L == R) {
        return arr[L];
    }
    int p1 = arr[L] + g(arr, L+1, R);
    int p2 = arr[R] + g(arr, L, R-1);

    return max(p1, p2);
}

// 后手函数，获得最好的分数
int g(vector<int> arr, int L, int R) {
    if (L == R) {
        return 0;
    }
    int p1 = f(arr, L+1, R); // 对手拿走L位置的数字
    int p2 = f(arr, L, R-1); // 对手拿走R位置的数字

    return min(p1, p2);
}
