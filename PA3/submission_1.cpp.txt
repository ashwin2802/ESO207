#include <cmath>
#include <cstdio>
#include <iostream>

#define MAX_STACK_SIZE 100000
#define WHITE 0
#define GRAY 1
#define BLACK -1

using namespace std;

struct stack{
    int top = 0;
    int data[MAX_STACK_SIZE];
};

struct edge
{
    int from;
    int to;
    int next;
};

struct vertex{
    int id;
    int d;
    int f;
    int pred_id;
    int color;
    
    vertex(int i)
    {
        id = i;
        d = f = 0;
        pred_id = -1;
        color = WHITE;
    }
};

struct graph{
    int v;
    int e;
    struct stack dfs_order;
    struct vertex* vertices;
    struct edge* edges;
    int* last_edges;
};

int isEmpty(struct stack* S)
{
    return (S->top == 0);
}

int isFull(struct stack* S)
{
    return (S->top == MAX_STACK_SIZE);
}

void push(struct stack* S, int key)
{
    if(!isFull(S)) S->data[++S->top] = key;
    return;
}

int pop(struct stack* S)
{
    if(!isEmpty(S)) return S->data[S->top--];
    else return -1;
}

struct graph make_graph(int i, int j)
{
    struct graph temp;
    temp.v = i; temp.e = j;
    
    temp.vertices = (struct vertex*) malloc(temp.v*sizeof(struct vertex));
    temp.edges = (struct edge*) malloc(temp.e*sizeof(struct edge));
    temp.last_edges = (int*) malloc(temp.v*sizeof(int));
    
    for(int k = 0; k < temp.v; k++)
    {
        temp.vertices[k] = vertex(k);
        temp.last_edges[k] = -1;
    }
    
    int start = 0, end = 0;
    for(int k = 0; k < temp.e; k++)
    {
        scanf("%d %d", &start, &end);
        temp.edges[k].from = start;
        temp.edges[k].to = end;
        temp.edges[k].next = temp.last_edges[start];
        temp.last_edges[start] = k;
    }
    
    return temp;
}

struct graph transpose(struct graph* g)
{
    struct graph temp;
    temp.v = g->v; temp.e = g->e;
    temp.vertices = (struct vertex*) malloc(temp.v*sizeof(struct vertex));
    temp.edges = (struct edge*) malloc(temp.e*sizeof(struct edge));
    temp.last_edges = (int*) malloc(temp.v*sizeof(int));
    
    for(int i = 0; i < temp.v; i++)
    {
        temp.vertices[i] = vertex(g->vertices[i].id);
        temp.last_edges[i] = -1;
    }
    
    for(int i = 0; i < temp.v; i++)
    {
        for(int j = g->last_edges[i]; j != -1; j = g->edges[j].next)
        {
            temp.edges[j].from = g->edges[j].to;
            temp.edges[j].to = g->edges[j].from;
            temp.edges[j].next = temp.last_edges[temp.edges[j].from];
            temp.last_edges[temp.edges[j].from] = j;
        }
    }
    
    return temp;
}

void dfs_visit(struct graph* g, struct vertex* u, int* t)
{
    *t = *t + 1;
    u->d = *t;
    u->color = GRAY;
    struct vertex* temp;
    for(int i = g->last_edges[u->id]; i != -1; i = g->edges[i].next)
    {
        temp = &(g->vertices[g->edges[i].to]);
        if(temp->color == WHITE)
        {
            temp->pred_id = u->id;
            dfs_visit(g, temp, t);
        }
    }
    push(&(g->dfs_order), u->id);
    u->color = BLACK;
    *t = *t + 1;
    u->f = *t;
}

int scc_visit(struct graph* g, struct vertex* u, int* t)
{
    *t = *t + 1; u->d = *t;
    u->color = GRAY;
    struct vertex* temp; int count = 1;
    for(int i = g->last_edges[u->id]; i != -1; i = g->edges[i].next)
    {
        temp = &(g->vertices[g->edges[i].to]);
        if(temp->color == WHITE)
        {
            temp->pred_id = u->id;
            count = count + scc_visit(g, temp, t);
        }
    }
    push(&(g->dfs_order), u->id);
    u->color = BLACK;
    *t = *t + 1; u->f = *t;
    return count;
}

void dfs(struct graph* g)
{
    int time = 0;
    for(int i = 0; i < g->v; i++)
    {
        if(g->vertices[i].color == WHITE)
        {
            dfs_visit(g, &(g->vertices[i]), &time);
        }
    }
}

void dfs(struct graph* g, struct stack* order, struct stack* l)
{
    int time = 0, id = 0;
    while(!isEmpty(order))
    {
        id = pop(order);
        if(id == -1) return;
        else
        {
            if(g->vertices[id].color == WHITE)
            {
                push(l, scc_visit(g, &(g->vertices[id]), &time));
            }
        }
    }
}

int main() {
    int t = 0, v = 0, e = 0;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d\n%d", &v, &e);
        struct graph g = make_graph(v, e);
        dfs(&g);
        struct graph t = transpose(&g);
        struct stack scc_lengths;
        dfs(&t, &(g.dfs_order), &scc_lengths);
        
        int max = 0, l = 0;
        while(!isEmpty(&scc_lengths))
        {
            l = pop(&scc_lengths);
            if(max <= l) max = l;
        }
        printf("%d\n", max);
    }
    return 0;
}
