#include <cmath>
#include <cstdio>
#include <iostream>

#define MAX_WEIGHT 10001

using namespace std;

struct edge{
    int from;
    int to;
    int w;
    int next;
};

struct vertex
{
    int id;
    int pred;
    int d;
    int p;
    
    vertex(int i)
    {
        id = i;
        pred = -1; 
        p = i;
        d = MAX_WEIGHT;
    }
};

struct graph{
    int v;
    int e;
    int heapsize;
    struct vertex* vertices;
    struct edge* edges;
    int* last_edges;
    int* heap;
};

struct graph make_graph(int i, int j)
{
    struct graph temp;
    temp.v = i; temp.e = j;
    
    temp.vertices = (struct vertex*) malloc(sizeof(struct vertex)*i);
    temp.last_edges = (int*) malloc(sizeof(int)*i);
    temp.edges = (struct edge*) malloc(sizeof(struct edge)*j);
    temp.heap = (int*) malloc(sizeof(int)*i);
    temp.heapsize = i;
    
    for(int k = 0; k < i; k++)
    {
        temp.vertices[k] = vertex(k);
        temp.last_edges[k] = -1;
        temp.heap[k] = k;
    }
    
    int start = 0, end = 0, weight = 0;
    for(int k = 0; k < j; k++)
    {
        scanf("%d %d %d", &start, &end, &weight);
        temp.edges[k].from = start;
        temp.edges[k].to = end;
        temp.edges[k].w = weight;
        temp.edges[k].next = temp.last_edges[start];
        temp.last_edges[start] = k;
    }
    
    return temp;
}

void min_heapify(struct graph* g, int index)
{
    int l = 2*index; int r = l + 1; int largest = 0;
    if(l < g->heapsize && g->vertices[g->heap[l]].d < g->vertices[g->heap[index]].d) largest = l;
    else largest = index;
    if(r < g->heapsize && g->vertices[g->heap[r]].d < g->vertices[g->heap[largest]].d) largest = r;
    if(largest != index)
    {
        int temp = g->heap[largest];
        g->heap[largest] = g->heap[index];
        g->heap[index] = temp;
        g->vertices[g->heap[index]].p = index;
        g->vertices[g->heap[largest]].p = largest;
        min_heapify(g, largest);
    }
}

void build_min_heap(struct graph* g)
{
    for(int i = g->heapsize/2; i > 0; i--)
    {
        min_heapify(g, i);
    }
}


int extract_min(struct graph* g)
{
    int max = g->heap[0];
    g->heap[0] = g->heap[g->heapsize-1];
    g->vertices[g->heap[0]].p = 0;
    g->heapsize--;
    min_heapify(g, 0);
    return max;
}

void decrease(struct graph* g, int key, int index)
{
    g->vertices[g->heap[index]].d = key;
    while(index > 0 && g->vertices[g->heap[index/2]].d > g->vertices[g->heap[index]].d)
    {
        int temp = g->heap[index/2];
        g->heap[index/2] = g->heap[index];
        g->heap[index] = temp;
        g->vertices[g->heap[index]].p = index;
        g->vertices[g->heap[index/2]].p = index/2;
        index = index/2;
    }
}

void walk(struct graph* g, int s)
{
    g->vertices[s].d = 0;
    build_min_heap(g); int u = 0;
    struct vertex* temp;
    while(g->heapsize != 0)
    {
        u = extract_min(g);
        for(int i = g->last_edges[u]; i != -1; i = g->edges[i].next)
        {
            temp = &(g->vertices[g->edges[i].to]);
            if(temp->d > g->vertices[u].d + g->edges[i].w)
            {
                temp->d = g->vertices[u].d + g->edges[i].w;
                temp->pred = u;
                decrease(g, temp->d, temp->p);
            }
        }
    }
    
}

int main() {
    int v = 0, e = 0;
    scanf("%d %d", &v, &e);
    struct graph g = make_graph(v,e);
    int s = 0, t = 0;
    scanf("%d %d", &s, &t);
    walk(&g, s);
    printf("%d", g.vertices[t].d);
    return 0;
}
