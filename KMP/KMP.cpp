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
int *getNext(string p)
{
    int leng = p.length();
    int *next = new int[leng];
    next[0] = -1;
    int i = 0, j = -1;
    while(i<leng){
        if(j == -1 || p[i] == p[j]){
            ++i;++j;
            next[i] = j;
        }
        else
            j = next[j];
    }
    return next;
}
int KMP(string t, string p)
{
    int i = 0, j = 0, leng1 = t.length(), leng2 = p.length();
    int *next = getNext(p);
    while(i < leng1 && j < leng2){
        if(j == -1 || t[i] == p[j]){
            i++;j++;
        }
        else
            j = next[j];
    }
    delete[] next;
    if(j == leng2)
        return i - j;
    else 
        return -1;
}
int main()
{
    cout << KMP("abcd", "bc") << endl;
    return 0;
}