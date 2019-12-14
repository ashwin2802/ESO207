#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

int reduce(int* dim, int n)
{
    int cost[n][n];
    for(int i = 0; i < n; i++) cost[i][i] = 0;
    for(int l = 1; l < n; l++)
    {
        int sum = 0;
        for(int k = l-1; k >= 0 ; k--)
        {
            cost[k][l] = (int) INFINITY;
            for(int j = k; j < l; j++)
            {
                sum = cost[k][j] + cost[j+1][l] + dim[k]*dim[j+1]*dim[l+1];
                if(sum < cost[k][l]) cost[k][l] = sum;
            }
        }
    }
    return cost[0][n - 1];
}

int main() {
    int t = 0, n = 0;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        int dim[n+1];
        for(int i = 0; i <= n; i++)
        {
            scanf("%d", dim+i);
        }
        int res = reduce(dim, n);
        printf("%d\n", res);
    }
    return 0;
}
