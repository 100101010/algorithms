// RMQ问题
// 求区间最小值，多次查询，每次查询的复杂度都是O(1)
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <set>
#include <map>
#include <cstring>
#include <numeric>
using namespace std;
long long dp[100][100];
long long data[100];
void RMQ_init(int n){
    for(int i = 1;i <= n;++i)
        dp[i][0] = data[i];     // 此时长度为1，只有一个元素
    for(int j = 1;(1<<j) <= n;++j){
        // 长度要放到外层循环，保证每一个元素都被更新到
        for(int i = 1;i + (1<<j) <= n;++i){
            dp[i][j] = min(dp[i][j-1],dp[i+(1<<(j - 1))][j - 1]);
        }
    }
}
int main()
{
    int n, R, L;
    cin>>n;
    // 读入数据
    RMQ_init(n);
    // 查询
    int k = 0;
    long long que[100];
    for(int i = 1;i <= n;++i){
        if((1<<k) <= i)
            ++k;
        que[i] = k-1;
    }
    while(cin>>L>>R){
        int k = que[R - L + 1];
        cout<<min(dp[L][k],dp[R - (1<<k)+1][k])<<endl;
    }
    return 0;
}