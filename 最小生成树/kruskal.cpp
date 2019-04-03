// HDU-1233题解
// kruskal算法

#include <iostream>
#include <algorithm>
using namespace std;
struct Graph{
    int u, v;
    long value;
}graph[5000];
int fa[101];
int N, m;
int find(int x) {
    return fa[x] == x?x:fa[x] = find(fa[x]);
}

int kruskal() {
    long ans = 0;
    for(int i = 1; i <= N; i++)
        fa[i] = i;
    for(int i = 0; i < m; i++){
        int s1 = find(graph[i].u);
        int s2 = find(graph[i].v);
        if(s1 != s2){
            ans += graph[i].value;
            fa[s2] = s1;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    while(true){
        cin>>N;
        if(N == 0)
            break;
        m = (N - 1)*N/2;
        for(int i = 0; i < m; i++)
            cin>>graph[i].u>>graph[i].v>>graph[i].value;
        std::sort(graph, graph + m, [](struct Graph a, struct Graph b){return a.value < b.value;});
        cout<<kruskal()<<endl;
    }
    return 0;
}