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
long dist[110][110];
const int INF = 0x3c3c3c3c - 1;
void init() {
    memset(matrix, INF, sizeof(matrix));
    for(int i = 0; i <= n; i++){
        matrix[i][i] = 0;
    }
    memset(visit, false, sizeof(visit));
}
void floyd() {
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
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
        floyd();
        cout<<matrix[1][n]<<endl;
    }
    return 0;
}