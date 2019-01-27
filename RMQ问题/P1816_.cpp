#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <set>
#include <map>
#include <cstring>
#include <numeric>
#include <cmath>
using namespace std;
constexpr const int MAXN = 18;
constexpr const int INF = 1e9;
int num[2*(1<<MAXN)];
int n;
void init(int base){
    n = 1;
    while(n < base){
        n<<=1;
    }
    for(int i = 0; i < 2*n - 1; i++){
        num[i] = INF;
    }
}
void change_k(int k, int a){ // 将节点k的值赋为a
    k += n - 1;
    num[k] = a;
    while(k){
        k = (k - 1) >> 1;
        num[k] = min(num[2 * k + 1], num[2 * k + 2]);
    }
}
int get_min(int a, int b, int k, int l, int r){
    if(a <= l && b >= r)
        return num[k];
    else if(a >= r || b <= l)
        return INF;
    else{
        int lc = get_min(a, b, 2 * k + 1, l, (l+r) / 2);
        int rc = get_min(a, b, 2 * k + 2, (l+r) / 2, r);
        return min(lc, rc);
    }
}
int main()
{
    int m;
    cin >> n >> m;
    int rnt = n;
    init(n);
    int temp;
    for(int i = 0; i < rnt; i++)
    {
        cin >> temp;
        change_k(i, temp);
    }
    int a, b;
    // 这里还可以实现更改
    // int k, num;
    // cin >> k >> num;
    // change_k(k, num);
    for(int i = 0; i < m; i++)
    {
        cin >> a >> b;
        // --a;--b;    这里视题目而定
        int ret = get_min(a, b, 0, 0, n);
        cout << (ret == INF?INF:ret) << endl;
    }
    return 0;
}