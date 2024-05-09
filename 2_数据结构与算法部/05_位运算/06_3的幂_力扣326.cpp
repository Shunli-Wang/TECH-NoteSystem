#include<iostream>
using namespace std;

class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n<=0) {return false;}
        while (n/3*3 == n && n!=1) { // 借用整除可以取整操作
            n /= 3;
        }
        return n == 1 ? true : false;
    }

    // 左神的位操作方法
    
};

