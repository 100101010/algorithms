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
#include <stack>
using namespace std;
long matrix[110][110]; // 领接矩阵表示的路径
int n, m;// n表示节点数，m表示边数
bool visit[110];
long long dist[110];
const int INF = 0x3c3c3c3c - 1;
struct Edge{
    int start;
    int end;
    long long cost;
}edge[10010];

long long bellman_ford() {
    for(int i = 0; i <= n;i++)
        dist[i] = INF;
    dist[1] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m * 2; j++)
            dist[edge[j].end] = std::min(dist[edge[j].end], dist[edge[j].start] + edge[j].cost);
    }
    return dist[n];
}
int main()
{
    ios_base::sync_with_stdio(false);
    int start, end, dista;
    while(1){
        cin >> n >> m;
        if(n == 0 && m == 0)
            break;
        for (int i = 0; i < m; i++)
        {
            cin >> start >> end >> dista;
            edge[i].start = start; edge[i].end = end; edge[i].cost = dista;
            edge[i + m].start = end; edge[i + m].end = start; edge[i + m].cost = dista;
        }
        cout<<bellman_ford()<<endl;
    }
    return 0;
}