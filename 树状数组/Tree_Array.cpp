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
int tree[10000];
int NUM = 10000;

void update(int index, int n)
{
    for(int i = index;i<NUM;i += (i&-i))
        tree[i] += n;
}

int get_sum(int n)
{
    int ans = 0;
    for(int i = n;i>0;i -= (i&-i))
        ans += tree[i];
    return ans;
}
int main()
{
    int x;
    for(int i = 1;i<=10;i++){
        cin>>x;
        update(i, x);
    }
    cout<<get_sum(10)<<endl;
    return 0;
}