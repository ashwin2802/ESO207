#include <cmath>
#include <cstdio>
#include <iostream>

#define MAX_VERTICES 100000
#define WHITE 0
#define GRAY 1
#define BLACK -1

using namespace std;

struct edge
{
    int start;
    int end;
    int next;
};

struct stack
{
    int top = 0;
    struct edge data[MAX_VERTICES];
};

struct vertex{
    int id;
    int color;
    int pred;
    int d;
    int back;
    
    vertex(int i)
    {
        id = i;
        color = WHITE;
        d = 0;
        pred = back = -1;
    }
};

struct graph{
    int v;
    int e;
    struct vertex* vertices;
    struct stack bridges;
    int num_bridges;
    struct edge* edges;
    int* last_edges;
};

int isEmpty(struct stack* S)
{
    return (S->top == 0);
}

int isFull(struct stack* S)
{
    return (S->top == MAX_VERTICES - 1);
}

void push(struct stack* S, struct edge key)
{
    if(!isFull(S))  S->data[++S->top] = key;
    return;
}

struct edge pop(struct stack* S)
{
    struct edge res;
    if(isEmpty(S))
    {
        res.start = res.end = res.next = -1;
    }
    else
    {
        res = S->data[S->top--];
    }
    return res;
}

struct graph make_graph(int i, int j)
{
    struct graph temp;
    temp.v = i; temp.e = j;
    temp.vertices = (struct vertex*) malloc(temp.v*sizeof(struct vertex));
    temp.edges = (struct edge*) malloc(2*temp.e*sizeof(struct edge));
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
        temp.edges[2*k].start = start;
        temp.edges[2*k].end = end;
        temp.edges[2*k].next = temp.last_edges[start];
        temp.last_edges[start] = 2*k;
        temp.edges[2*k + 1].start = end;
        temp.edges[2*k + 1].end = start;
        temp.edges[2*k + 1].next = temp.last_edges[end];
        temp.last_edges[end] = 2*k + 1;
    }
    
    temp.num_bridges = 0;
    return temp;
}

void dfs_visit(struct graph* g, struct vertex* v, int* t)
{
    *t = *t + 1; 
    v->d = *t;
    v->back = v->d;
    v->color = GRAY;
    struct vertex* temp;
    struct edge bridge;
    for(int i = g->last_edges[v->id]; i != -1; i = g->edges[i].next) 
    {
        temp = &(g->vertices[g->edges[i].end]);
        if(temp->color == WHITE)
        {
            temp->pred = v->id;
            dfs_visit(g, temp, t);
            v->back = min(v->back, temp->back);
            if(temp->back > v->d)
            {
                bridge.start = v->id;
                bridge.end = temp->id;
                bridge.next = -1;
                push(&(g->bridges), bridge);
                g->num_bridges++;
            }
        }
        else if(temp->id != v->pred)
        {
            v->back = min(v->back, temp->d);
        }
    }
    v->color = BLACK;
}

void find_bridges(struct graph* g)
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

int main() {
    int v = 0, e = 0;
    scanf("%d %d", &v, &e);
    struct graph k = make_graph(v,e);
    find_bridges(&k);
    
    if(k.num_bridges == 0) printf("No");
    else
    {
        struct edge bridge;
        while(!isEmpty(&(k.bridges)))
        {
            bridge = pop(&(k.bridges));
            printf("%d %d\n", bridge.start, bridge.end);
        }
    }
    
    return 0;
}