#include <cmath>
#include <cstdio>
#include <iostream>

#define MAX_QUEUE_SIZE 10000
#define WHITE 0
#define RED 1
#define BLUE -1

using namespace std;

struct queue{
    int head = 0;
    int tail = 0;
    int data[MAX_QUEUE_SIZE];
};

struct vertex{
    int id;
    int color;
    
    vertex(int i)
    {
        id = i;
        color = WHITE;
    }
};

struct edge{
    int from;
    int to;
    int next;
};

struct graph{
    int v;
    int e;
    struct vertex* vertices;
    struct edge* edges;
    int* last_edges;
};

int isFull(struct queue* Q)
{
    return(Q->head == Q->tail+1);
}

int isEmpty(struct queue* Q)
{
    return(Q->head == Q->tail);
}

void enqueue(struct queue* Q, int key)
{
    if(isFull(Q)) return;
    else
    {
        Q->data[Q->tail] = key;
        if(Q->tail == MAX_QUEUE_SIZE - 1) Q->tail = 0;
        else Q->tail = Q->tail + 1;
    }
}

int dequeue(struct queue* Q)
{
    if(isEmpty(Q)) return -1;
    else
    {
        int res = Q->data[Q->head];
        if(Q->head == MAX_QUEUE_SIZE - 1) Q->head = 0;
        else Q->head = Q->head + 1;
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
    
    for(int k = 0; k < temp.v; k++)
    {
        temp.vertices[k] = vertex(k);
        temp.last_edges[k] = -1;
    }
    
    int start = 0, end = 0;
    for(int k = 0; k < temp.e; k++)
    {
        scanf("%d %d", &start, &end);
        start--; end--;
        temp.edges[2*k].from = start;
        temp.edges[2*k].to = end;
        temp.edges[2*k].next = temp.last_edges[start];
        temp.last_edges[start] = 2*k;
        temp.edges[2*k + 1].from = end;
        temp.edges[2*k + 1].to = start;
        temp.edges[2*k + 1].next = temp.last_edges[end];
        temp.last_edges[end] = 2*k + 1;
    }
    return temp;
}

int check(struct graph* g, struct vertex* s)
{
    struct queue buf;
    struct vertex* temp;
    enqueue(&buf, s->id);
    while(!isEmpty(&buf))
    {
        int u = dequeue(&buf);
        for(int i = g->last_edges[u]; i != -1; i = g->edges[i].next)
        {
            temp = &(g->vertices[g->edges[i].to]);
            if(temp->color == WHITE)
            {
                temp->color = (-1)*g->vertices[u].color;
                enqueue(&buf, temp->id);
            }
            else if(temp->color != (-1)*g->vertices[u].color)
            {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int t = 0, v = 0, e = 0;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &v, &e);
        struct graph g = make_graph(v, e);
        
        int result = 0;
        for(int i = 0; i < g.v; i++)
        {
            if(g.vertices[i].color == WHITE)
            {
                g.vertices[i].color = RED;
                result = check(&g, &(g.vertices[i]));
            }
            if(result) continue;
            else break;
        }
        printf(result ? "Yes\n" : "No\n");
    }
    return 0;
}
