#include <cmath>
#include <cstdio>
#include <iostream>

#define MAX_VERTICES 10000
#define WHITE 0
#define GRAY 1
#define BLACK -1

using namespace std;

struct queue
{
    int head = 0;
    int tail = 0;
    int data[MAX_VERTICES];
};

struct vertex
{
    int id;
    int color;
    int d_pred;
    int b_pred;
    int dist;
    int disc;
    int back;
    
    vertex(int i)
    {
        id = i;
        disc = 0;
        color = WHITE;
        d_pred = b_pred = dist = back = -1;
    }
};

struct edge
{
    int start;
    int end;
    int next;
};

struct graph
{
    int v;
    int e;
    struct vertex* vertices;
    struct edge bridge;
    struct edge* edges;
    int* last_edges;
};

int isFull(struct queue* q)
{
    return (q->head == q->tail + 1);
}

int isEmpty(struct queue* q)
{
    return (q->head == q->tail);
}

void enqueue(struct queue* q, int key)
{
    if(isFull(q)) return;
    else
    {
        q->data[q->tail] = key;
        if(q->tail == MAX_VERTICES) q->tail = 0;
        else q->tail = q->tail + 1;
    }
}

int dequeue(struct queue *q)
{
    if(isEmpty(q)) return -1;
    else
    {
        int res = q->data[q->head];
        if(q->head == MAX_VERTICES) q->head = 0;
        else q->head = q->head + 1;
        return res;
    }
}

struct graph make_graph(int i, int j)
{
    struct graph temp;
    temp.v = i; temp.e = j;
    temp.vertices = (struct vertex*) malloc(temp.v*sizeof(struct vertex));
    temp.edges = (struct edge*) malloc(2*temp.e*sizeof(struct edge));
    temp.last_edges = (int*) malloc(temp.v*sizeof(int));
    
    for(int k=0; k<temp.v; k++)
    {
        temp.vertices[k] = vertex(k);
        temp.last_edges[k] = -1;
    }

    int start = 0, end = 0;    
    for(int k=0; k<temp.e; k++)
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
    
    temp.bridge.start = temp.bridge.end = temp.bridge.next = -1;
    return temp;
}

void dfs_visit(struct graph* g, struct vertex* u, int* t)
{
    *t = *t + 1;
    u->disc= u->back =*t;
    u->color = GRAY;
    struct vertex* v;
    for(int i = g->last_edges[u->id]; i != -1; i = g->edges[i].next)
    {
        v = &(g->vertices[g->edges[i].end]);
        if(v->color == WHITE)
        {
            v->d_pred = u->id;
            dfs_visit(g, v, t);
            u->back = min(u->back, v->back);
            if(v->back > u->disc)
            {
                g->bridge.start = u->id;
                g->bridge.end = v->id;
            }
        }
        else if(v->id != u->d_pred)
        {
            u->back = min(u->back, v->disc);
        }
    }
    u->color = BLACK;
}

void find_connector(struct graph* g)
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

void walk(struct graph* g, struct vertex* s)
{
    struct queue buf;
    struct vertex* v;
    int u = 0;
    s->color = GRAY;
    s->dist = 0;
    enqueue(&buf, s->id);
    while(!isEmpty(&buf))
    {
        u = dequeue(&buf);
        for(int i = g->last_edges[u]; i != -1; i = g->edges[i].next)
        {
            v = &(g->vertices[g->edges[i].end]);
            if(v->color == WHITE)
            {
                v->color = GRAY;
                v->dist = g->vertices[u].dist + 1;
                v->b_pred = u;
                enqueue(&buf, v->id);
            }
        }
        g->vertices[u].color = BLACK;
    }
}

int main() {
    int v = 0, e = 0, q = 0;
    scanf("%d %d %d", &v, &e, &q);
    struct graph k = make_graph(v, e);
    find_connector(&k);
    
    for(int i = 0; i < k.v; i++)
    {
        k.vertices[i].color = WHITE;
    }
    k.vertices[k.bridge.end].color = BLACK;
    
    walk(&k, &(k.vertices[k.bridge.start]));
    
    k.vertices[k.bridge.start].color = BLACK;
    k.vertices[k.bridge.end].color = WHITE;
    walk(&k, &(k.vertices[k.bridge.end]));
    
    int start = 0, end = 0, dist = 0;
    for(int i = 0; i < q; i++)
    {
        scanf("%d %d", &start, &end);
        dist = k.vertices[start].dist + 1 + k.vertices[end].dist;
        printf("%d\n", dist);
    }
    
    return 0;
}