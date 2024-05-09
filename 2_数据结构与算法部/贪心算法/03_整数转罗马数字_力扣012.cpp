// https://leetcode.cn/problems/integer-to-roman/
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

struct cmp{
    bool operator()(int a, int b){
        return a > b;
    }
};

class Solution {
public:

    string intToRoman(int num) {
        unordered_map<int, string> map;
        map[1] = "I"; map[4] = "IV";
        map[5] = "V"; map[9] = "IX";
        map[10] = "X"; map[40] = "XL";
        map[50] = "L"; map[90] = "XC";
        map[100] = "C"; map[400] = "CD";
        map[500] = "D"; map[900] = "CM";
        map[1000] = "M";

        vector<int> allChange;
        for (auto& info : map) allChange.push_back(info.first);
        sort(allChange.begin(), allChange.end(), cmp());

        string ans = "";
        for (int& chge : allChange) {
            int cnt = num / chge; // 能够进行整除，则按照结果添加
            if (cnt != 0) {
                for (int i=0; i<cnt; i++) ans += map[chge];
                num %= chge; // 取余数继续进行
                if (num == 0) break; // 如果达到了目的，退出
            }
        }

        return ans;
    }
};
