#include <cmath>
#include <iostream>
#include <cstdio>

#define ERROR INT8_MIN
#define MAX_STACK_SIZE 1000
#define OPER_TYPE 0

using namespace std;

int get_id(int c){
    switch(c){
        default: return 0;
        case 40: return 7;
        case 41: return 1;
        case 42: return 5;
        case 43: return 3;
        case 45: return 2;
        case 47: return 4;
        case 94: return 6;
    }
}

struct token{
    int type = -1;
    int oper;
    int op;
};

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

struct token get_token(){
    struct token tok; 
    int c = getchar();
    if(c < 40 || c > 122) return tok;
    else tok.type = get_id(c);
    if(tok.type == OPER_TYPE) tok.oper = c;
    else tok.op = c;
    return tok;
}

int main() {
    struct token tok; struct stack ops;
    int postfix[MAX_STACK_SIZE]; 
    int index = 0, ret_val = 0;
    tok = get_token();
    while(tok.type > -1 && index < MAX_STACK_SIZE){
        if(tok.type == OPER_TYPE) postfix[index++] = tok.oper;
        else if(tok.type == 1){
            while(!isEmpty(&ops) && get_id(top(&ops)) != 7) postfix[index++] = pop(&ops);
            ret_val = pop(&ops);
        }
        else if(!isEmpty(&ops) && tok.type <= get_id(top(&ops))){
            while(!isEmpty(&ops) && tok.type <= get_id(top(&ops))){
                if(get_id(top(&ops)) == 7) break;
                postfix[index++] = pop(&ops);
            }
            if(push(&ops, tok.op) == ERROR) return -1;
        }
        else if(push(&ops, tok.op) == ERROR) return -1;
        tok = get_token();
    }
    while(!isEmpty(&ops)) postfix[index++] = pop(&ops);
    index = 0;
    while(postfix[index] < 123 && postfix[index] > 39 && index < MAX_STACK_SIZE) printf("%c", postfix[index++]); 
    return 0;
}
