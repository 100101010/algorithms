// HDU-1301题解
// prime算法

#include <iostream>
#include <cstring>
using namespace std;
int N, number, value;
char head, to;
int graph[27][27];
bool visit[27];
int prime() {
    int ans = 0, u, count = 0;
    visit[0] = true;
    while(count < N - 1){
        int tmp = -1;
        for(int i = 0; i < N; ++i){
            if(visit[i] == false)     // 如果这个节点还没有加入到路径之中，就不要
                continue;
            for(int j = 0; j < N; ++j){ // 当某一节点已加入到路径中，那么搜索他的最短路径
                if(visit[j] == false && graph[i][j] != -1 && (graph[i][j] < tmp || tmp == -1)){
                    tmp = graph[i][j];u = j;
                }
            }
        }
        if(tmp != -1){
            visit[u] = true;
            ans += tmp;
            ++count;
        }
    }
    return ans;
}
int main()
{
    while(true){
        cin>>N;
        if(N == 0)
            break;
        memset(graph, -1, sizeof(graph));
        memset(visit, false, sizeof(visit));
        for(int i = 0; i < N - 1; ++i){
            cin>>head>>number;
            if(number == 0)
                continue;
            for(int j = 0; j < number; ++j){
                cin>>to>>value;
                graph[head - 'A'][to - 'A'] = value;
                graph[to - 'A'][head - 'A'] = value;
            }
        }
        cout<<prime()<<endl;
    }
    return 0;
}