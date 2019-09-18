nclude <cstdio>
#include <iostream>
using namespace std;

/* function to execute binary search on a sorted array */
int search(long* arr, int p, int r, long key){
    if(p>r) return -1; // p cannot be greater than r
    if(p==r){   // only one element
        if(arr[p]==key) return p;  // element is the key
        else return -1;  // key not in array
    }
    int q = (p+r)/2;  // midpoint
    if(arr[q]==key) return q;  // key found
    // if key is less than current element it lies in the right half
    else if(arr[q]>key) return search(arr, p, q, key); // search left half
    else return search(arr, q+1, r, key); // search right half
}

/* function to find index of least element in RSA */
int num_shift(long* arr, int p, int r){
    if(p>=r) return 0;  // p cannot be greater than r
    int q = (p+r)/2;  // midpoint
    // preceding element is greater than current element for the least element only
    if(arr[q] < arr[q-1]) return q; // least element 
    // least element lies to right of current element if it is greater than first element
    if(arr[q] >= arr[0]) return num_shift(arr, q+1, r);  // search the right half
    else return num_shift(arr, p, q);  // search the left half
}

int main(){
    int t=0, n=0, index=0; long k=0;  // variable declaration
    scanf("%d", &t);  // number of testcases
    for(int i=0; i<t; i++){
        scanf("%d", &n);  // length of array
        long* input = (long*) calloc(sizeof(long), n);  // memory allocation
        for(int j=0; j<n; j++) scanf("%ld", input+j);  // fill array
        scanf("%ld", &k);  // element to search for (key)
        int shift = num_shift(input, 0, n-1);  // find index of least element
        if(input[shift] == k) index = shift;  // if key is least element, done
        else{
            // if least element is first, array is completely sorted
            if(shift == 0) index = search(input, 0, n-1, k); // execute binary search on whole array
            else{
                if (*input == k) index = 0;  // if first element is key, done
                // if first element is greater than key, key comes after the least element
                else if(*input > k) index = search(input, shift+1, n-1, k); // execute binary search on second part of array
                // if first element is less than key, key comes before the least element
                else index = search(input, 0, shift-1, k);  // execute binary search on first part of array
            }
        }
        printf("%d\n", index);  // output
    }
    return 0;
}
