#include <cmath>
#include <cstdio>
#include <iostream>
#define max(a,b) ((a)>(b)) ? (a) : (b)
using namespace std;

int find_lcs(char* s1, char* s2, int m, int n)
{
    int len[2][n+1]; 
    
    len[1][0] = 0;
    for(int j =0; j <=n; j++) len[0][j] = 0;
    
    int k = 0;
    for(int i = 1; i <= m; i++)
    {
        k = i%2;
        for(int j = 1; j <= n; j++)
        {
            if(s1[i-1] == s2[j-1]) len[k][j] = 1 + len[1-k][j-1];
            else len[k][j] = max(len[k][j-1], len[1-k][j]);
        }
    }
    return len[m%2][n];
}

int main() {
    int t = 0, m = 0, n = 0;
    scanf("%d\n", &t);
    while(t--)
    {
        scanf("%d %d\n", &m, &n);
        char s1[m], s2[n];
        for(int i = 0; i < m; i++) scanf("%c", s1+i);
        scanf("\n");
        for(int i = 0; i < n; i++) scanf("%c", s2+i);
        int l = find_lcs(s1, s2, m, n);
        printf("%d\n", l);
    }
    return 0;
}
