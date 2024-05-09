
```c++
// 一般图的题目下标从1开始到n
int MAXN = 10001;
int* father = new int[MAXN];

void build(int n) {
    for (int i=1; i<=n; i++) {
        father[i] = i;
    }
}

int find(int i) {
    if (father[i] != i) {
        father[i] = find(father[i]);
    }
    return father[i];
}

bool unionSet(int a, int b) {
    int fa = find(a); // !!! 这里是find，不是father
    int fb = find(b);
    if (fa != fb) {
        father[fa] = fb; // 操纵父节点的指向，而不是原始节点ab的指向
        return false;
    } else {
        return true;
    }
}

```
