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
int minDistance(string word1, string word2) {
    int dp[100][100];
    memset(dp,0,sizeof(dp));
    int leng1 = word1.length();
    int leng2 = word2.length();
    for(int i = 0;i<=leng1;i++)
        dp[i][0] = i;
    for(int i = 0;i<=leng2;i++)
        dp[0][i] = i;
    for(int i=1;i<=leng1;i++){
        for(int j=1;j<=leng2;j++){
            if(word1[i-1]==word2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]))+1;
        }
    }
    return dp[leng1][leng2];
}
int main()
{
    cout << minDistance("abd","abc") << endl;
    return 0;
}