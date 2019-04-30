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
long dist[110];
const int INF = 0x3c3c3c3c - 1;
void init() {
    memset(matrix, INF, sizeof(matrix));
    for(int i = 0; i <= n; i++){
        matrix[i][i] = 0;
    }
    memset(visit, false, sizeof(visit));
}
void dijkstra(int start) {
    visit[start] = true;
    for(int i = 1; i <= n; i++){
        dist[i] = matrix[start][i];
    }
    int k, minDist;
    for(int i = 1; i <= n; i++){
        minDist = INF;  // 初始化最小距离为特别大
        // 找出未访问的最小距离的结点
        for(int j = 1; j <= n; j++){
            // 如果j结点没有访问，且start到j可达，到达距离小于minDist
            if(visit[j] == false && dist[j] < minDist){
                minDist = dist[j];
                k = j;
            }
        }
        if(minDist == INF)
            break;
        // 标记k结点被访问
        visit[k] = true;
        // 更新结点
        for(int j = 1; j <= n;j++){
            if(dist[j] > minDist + matrix[k][j]) {
                dist[j] = minDist + matrix[k][j]; // 松弛操作
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    int start, end, dista;
    while(1){
        cin >> n >> m;
        if(n == 0 && m == 0)
            break;
        init();
        for (int i = 0; i < m; i++)
        {
            cin >> start >> end >> dista;
            matrix[start][end] = dista;
            matrix[end][start] = dista;
        }
        dijkstra(1);
        cout<<dist[n]<<endl;
    }
    return 0;
}