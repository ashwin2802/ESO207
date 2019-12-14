#include <cmath>
#include <cstdio>
#include <iostream>
#define ERROR INT8_MIN
#define MAX_STACK_SIZE 1000000
using namespace std;

struct stack{
    int top = 0;
    int data[MAX_STACK_SIZE];
};

int isEmpty(struct stack* S){ return (S->top == 0); }

int isFull(struct stack* S){ return (S->top == MAX_STACK_SIZE); }

int push(struct stack* S, int key){
    if(isFull(S)) return ERROR;
    else{
        S->data[++S->top] = key;
        return 0;
    }
}

int pop(struct stack* S){
    if(isEmpty(S)) return ERROR;
    else{
        int x = S->data[S->top--];
        return x;
    }
}

int top(struct stack* S){ return S->data[S->top]; }

int main() {
    int t = 0, n = 0, h = 0;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        int street[n+1], jumps[n], ret_val = 0;
        struct stack swing; street[0] = (int) INFINITY;
        for(int i = 0; i < n; i++){ scanf("%d", street+i+1); }
        for(int i = 1; i <= n; i++){
            while(!isEmpty(&swing) && street[i] >= street[top(&swing)]){ ret_val = pop(&swing); }
            jumps[i-1] = isEmpty(&swing) ? 0 : top(&swing);
            if(push(&swing, i) == ERROR) return -1;
        }
        for(int i = 1; i <= n; i++){ printf("%d\n", i - jumps[i-1]); }
    }
    return 0;
}