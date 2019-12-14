#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int v = 0, e = 0, q = 0;
int x = 0, y = 0, w = 0;

struct edge{
    int x; 
    int y; 
    int w;
};

struct edge* edges;
struct edge* mst;
int *parent, *ranx;
struct edge n;

int find(int x)
{
    if(x != parent[x]) parent[x] = find(parent[x]);
    return parent[x];
}

void combine(int a, int b)
{
    a = find(a); b = find(b);
    if(ranx[a] >= ranx[b]) parent[b] = a;
    else parent[a] = b;
    if(ranx[a] == ranx[b]) ranx[a]++;
}

void merge(struct edge* e, int i, int l, int j)
{
    struct edge left[l - i + 1];
    struct edge right[j - l];
    for(int k = 0; k < l - i + 1; k++) left[k] = e[i+k];
    for(int k = 0; k < j - l; k++) right[k] = e[l + 1 + k];
    
    int pl = 0, pr = 0, pm = i;
    while(pl < l - i + 1 && pr < j - l)
    {
        if(left[pl].w <= right[pr].w) e[pm++] = left[pl++];
        else e[pm++] = right[pr++];
    }
    
    while(pl < l - i + 1) e[pm++] = left[pl++];
    while(pr < j - l) e[pm++] = right[pr++];
}

void sort(struct edge* e, int i, int j)
{
    if(i >= j) return;
    int l = (i+j)/2;
    sort(e, i, l);
    sort(e, l+1, j);
    merge(e, i, l, j);
}

int main() {
    
    int j = 0, k = 0, a = 0;
    int b = 0, res = 0, l = 0;
    
    scanf("%d %d %d", &v, &e, &q);
    
    edges = (struct edge*) malloc(sizeof(struct edge)*(e));
    mst = (struct edge*) malloc(sizeof(struct edge)*(v));
    parent = (int*) malloc(sizeof(int)*v);
    ranx = (int*) malloc(sizeof(int)*v);
    
    for(int i = 0; i < e; i++) 
    {
        scanf("%d %d %d", &x, &y, &w);
        edges[i].x = x; edges[i].y = y; edges[i].w = w;
    }
    
    for(int i = 0; i < v; i++)
    {
        parent[i] = i;
        ranx[i] = 0;
    }
    
    sort(edges, 0, e - 1);
    
    for(int i = 0; i < e; i++)
    {
        a = edges[i].x; b = edges[i].y;
        j = find(a), k = find(b);
        if(j != k)
        {
            res += edges[i].w;
            mst[l++] = edges[i];
            combine(j, k);
        }
    }
    printf("%d\n", res);
    
    while(q--)
    {
        scanf("%d %d %d", &x, &y, &w);
        n.x = x; n.y = y; n.w = w;
        
        int m = 0; res = 0, l = 0; 
        while(w > mst[m].w) m++;
        for(int i = v - 1; i >= m; i--) mst[i] = mst[i-1];
        mst[m] = n;
        
        for(int i = 0; i < v; i++)
        {
            parent[i] = i;
            ranx[i] = 0;
        }
        
        for(int i = 0; i < v; i++)
        {   
            a = mst[i].x; b = mst[i].y;
            j = find(a), k = find(b);
            if(j != k)
            {
                res += mst[i].w;
                mst[l++] = mst[i];
                combine(j, k);
            }
        }
        printf("%d\n", res);   
    }
    return 0;
}
