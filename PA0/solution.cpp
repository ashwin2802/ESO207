#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long find_fib(int n, long* fib){
    if(n == 0) return 0;
    if(n == 1){
        if(*(fib + 1) == 0) *(fib+1) = 1;
        return 1;
    }
    if(*(fib + n) == 0) *(fib + n) = find_fib(n-1, fib) + find_fib(n-2, fib);
    return *(fib+n);
}

int main() {
    int n = 0;
    long sum = 0;
    scanf("%d", &n);
    long* fib = (long*) calloc(sizeof(long), n);
    for(int i = 0; i<n; i++) sum += find_fib(i, fib);
    printf("%ld\n", sum);
    // for(int i = 0; i<n; i++) printf("%ld", *(fib+i));
    return 0;
}

