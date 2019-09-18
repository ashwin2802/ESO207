#include <cstdio>
#include <iostream>
using namespace std;

/* function to count inversions in an array while sorting*/
int count_inversions(long* arr, int p, int r){
    if(p>=r) return 0;  // p cannot be greater than r
    int q = (p+r)/2;
    // divide step, count inversions within each half
    int inversions = count_inversions(arr, p, q) + count_inversions(arr, q+1, r);
    // divide into two subarrays
    long* left_arr = (long*) malloc(sizeof(long)*(q-p+2));
    long* right_arr = (long*) malloc(sizeof(long)*(r-q+1));
    for(int i=p; i<=r; i++){
        if(i>q) right_arr[i-(q+1)] = arr[i];
        else left_arr[i-p] = arr[i];
    }
    left_arr[q-p+1] = right_arr[r-q] = __LONG_MAX__; // last element is padding
    int left_index = p, right_index = q+1;  // initialize counters
    // merge step, count inversions across halves
    for(int k=p; k<=r; k++){
        if(left_arr[left_index-p] <= right_arr[right_index-(q+1)]){
            arr[k] = left_arr[left_index-p];
            left_index++;
        }
        else{
            arr[k] = right_arr[right_index-(q+1)];
            right_index++;
            // when element merges from right it has inversions with all unmerged elements in the left
            inversions += q - left_index + 1;
        }
    }
    return inversions;
}

int main() {
    int t = 0, n = 0;  // variable declaration
    scanf("%d", &t);  // number of testcases
    for(int i=0; i<t; i++){
        scanf("%d", &n);  // length of array
        long* input = (long*) calloc(sizeof(long), n);  // memory allocation
        for(int j=0; j<n; j++) scanf("%ld", input+j);  // fill array
        printf("%d\n", count_inversions(input, 0, n-1));  // output
    }
    return 0;
}
