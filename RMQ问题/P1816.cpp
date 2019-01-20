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
#include <fstream>
using namespace std;
int a[100005][20],m,n;
int main()
{
    /*ifstream in("in.txt");
    ofstream out("out.txt");*/
    cin>>n>>m;
    for(int i = 1;i<=n;i++){
        cin>>a[i][0];
    }
    for(int j = 1;j<=20;j++){
        for(int i = 1;i<=n;i++){
            if(i+(1<<j)-1<=n)
                a[i][j] = min(a[i][j-1],a[i+(1<<(j-1))][j-1]);
        }
    }
    int l,r;
    while(m--){
        cin>>l>>r;
        int k = log2(r-l+1);
        cout<<min(a[l][k],a[r-(1<<k)+1][k])<<" ";
    }
    return 0;
}