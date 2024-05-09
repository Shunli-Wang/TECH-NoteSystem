
# 题目1: 37. 解数独(DFS恢复现场)[Hard]
https://leetcode.cn/problems/sudoku-solver/

```c++
// 假设ij都是合法的
bool process(
    vector<vector<char>>& arr, 
    int i, int j, 
    vector<vector<bool>>& row, 
    vector<vector<bool>>& col, 
    vector<vector<bool>>& bkt) 
    {

    if (i == 9) return true; // 来到最后一行，能够填完
    int nexti = j == 8 ? i + 1 : i;
    int nextj = j == 8 ? 0 : j + 1;
    
    if (arr[i][j] != '.') { // 是数字，新找位置 
        return process(arr, nexti, nextj, row, col, bkt);
    } else { // 是点，需要尝试填写
        int bid = 3*(i/3)+(j/3);
        for (int num = 1; num <= 9; num++) {
            if (!(row[i][num] || col[j][num] || bkt[bid][num])) { // 已经填过了，跳过
                // 制造DFS现场
                row[i][num] = true;
                col[j][num] = true;
                bkt[bid][num] = true;
                arr[i][j] = '0' + num;
                if (process(arr, nexti, nextj, row, col, bkt)) {
                    return true; // 后续但凡有一个能跑出来，就返回true
                }
                // 恢复DFS现场
                row[i][num] = false;
                col[j][num] = false;
                bkt[bid][num] = false;
                arr[i][j] = '.';
            }
        }
    }
    return false; // 找完了还是没有发现可行方案，无法解决
}

void solveSudoku(vector<vector<char>>& board) {
    // 完成所有的标记
    vector<vector<bool>> row(9, vector<bool>(10));
    vector<vector<bool>> col(9, vector<bool>(10));
    vector<vector<bool>> bkt(9, vector<bool>(10));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.') {
                int ch = board[i][j];
                row[i][ch-'0'] = true;
                col[j][ch-'0'] = true;
                bkt[3*(i/3)+(j/3)][ch-'0'] = true;
            }
        }
    }
    process(board, 0, 0, row, col, bkt);
}
```

# 题目2: 79. 单词搜索(DFS恢复现场)[Medium]
https://leetcode.cn/problems/word-search/

```c++
vector<vector<int>> moves = {{0,1},{1,0},{0,-1},{-1,0}};

/* V3. k位置卡word版本，原表中标记无效位 */
// 含义: 从ij位置开始，能不能从k位置开始匹配出来word
bool p(vector<vector<char>>& board, int i, int j, string& word, int k) {
    if (k == word.size()) return true; // 得写到第一个
    if (i < 0 || i == board.size() || j < 0 || j == board[0].size()) return false; // 越界
    if (board[i][j] != word[k]) return false; // 开始就不匹配

    bool ans = false;
    char temp = board[i][j]; // 暂存此位置
    board[i][j] = 0; // 先修改为无效数值
    for (auto& move : moves) {
        int ni = i + move[0];
        int nj = j + move[1];
        if (p(board, ni, nj, word, k+1)) ans = true; // 后面但凡能有一个路走通可以返回，就返回true
    }
    board[i][j] = temp; // 恢复现场

    return ans;
}

bool exist(vector<vector<char>>& board, string word) {
    int m = board.size();
    int n = board[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (p(board, i, j, word, 0)) return true;
        }
    }
    return false;
}
```

# 题目3: 17. 电话号码的字母组合(DFS路径收集)[Medium]
https://leetcode.cn/problems/letter-combinations-of-a-phone-number/description/

```c++
vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) return {};
    map<int, string> table;
    table[2] = "abc"; table[3] = "def"; 
    table[4] = "ghi"; table[5] = "jkl"; 
    table[6] = "mno"; table[7] = "pqrs";
    table[8] = "tuv"; table[9] = "wxyz";
    vector<string> digList; // ["abc", "def"]
    string path = "";
    for (char& ch : digits) {
        digList.push_back(table[ch - '0']);
        path = path + " "; // 先构造一个path，长度就是最终的目标
    }
    vector<string> ans;
    process(digList, 0, path, ans);
    return ans;
}

// 我现在开始决策i位置的字符，digs[i]存放着所有的选择，收集所有可能情况
void process(vector<string> digList, int i, string& path, vector<string>& ans) {
    if (i == digList.size()) { // 到达结尾位置，保存结果
        ans.push_back(path); 
        return; // 不要忘记了这个返回
    }
    for (char ch : digList[i]) {
        path[i] = ch;
        process2(digList, i + 1, path, ans);
    }
}
```

# 题目4: 22. 括号生成(DFS剪枝)[Medium]
https://leetcode.cn/problems/generate-parentheses/description/

DFS的过程中通过合法性校验进行剪枝。

```c++
void process(int n, int m, int flag, string path, vector<string>& ans) {
    if (flag < 0) return ; // 非法情况
    if (n == 0 && m == 0) {
        ans.push_back(path); // 到达终止情况，记录返回
        return ;
    }
    if (n != 0) process(n-1, m, flag+1, path+'(', ans); // 可以加'('
    if (m != 0) process(n, m-1, flag-1, path+')', ans); // 可以加')'
}

vector<string> generateParenthesis(int n) {
    vector<string> ans;
    process(n, n, 0, "", ans);
    return ans;
}
```

# 题目5: 46. 全排列(DFS恢复现场)[Medium]
https://leetcode.cn/problems/permutations/

使用原位记录的做法规避掉path变量的引入，也属于DFS恢复现场技巧。

```c++
// 标记位置idx，从idx位置开始自由选择。通过位置调换操作避免其他数据结构引入
void process(vector<int>& nums, int idx, vector<vector<int>>& ans) {
    if (idx == nums.size()) {
        ans.push_back(nums);
        return ;
    }
    for (int i = idx; i < nums.size(); i++) {
        swap(nums[idx], nums[i]);
        process(nums, idx+1, ans);
        swap(nums[idx], nums[i]);
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    int len = nums.size();
    vector<vector<int>> ans;
    process(nums, 0, ans);
    return ans;
}
```


# 题目6: 47. 全排列II(DFS恢复现场)[Medium]
https://leetcode.cn/problems/permutations-ii/

属于拐弯题，使用set进行剪枝。

```c++
// 思路：避免交换两两相同的字符
void process(vector<int>& nums, int idx, vector<vector<int>>& ans) {
    if (idx == nums.size()) {
        ans.push_back(nums);
        return;
    }
    set<int> rec;
    for (int i = idx; i < nums.size(); i++) {
        if (rec.count(nums[i]) == 0) { // 之前没有使用过这个数值
            rec.insert(nums[i]); // 先加进去
            swap(nums[idx], nums[i]);
            process(nums, idx + 1, ans);
            swap(nums[idx], nums[i]);
        }
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> ans;
    process(nums, 0, ans);
    return ans;
}
```




