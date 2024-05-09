#include<iostream>
#include<set>
using namespace std;

int main() {
    unsigned long n; cin >> n;
    set<int> allSet;

    // 枚举各种家的数量，set存放每个家能分到的重量
    int j;
    for (j=1; j<=n; j++) {
        allSet.insert(n / j);
    }

    cout << allSet.size();

    return 0;
}

// 粮食公司从农场收购了n吨粮食，现在要要平均分配给分销商进行销售(除不尽向下取整)。
// 分销商数量若干，请计算分销商获得的粮食数量有几种可能。

