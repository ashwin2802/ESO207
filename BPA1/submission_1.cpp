#include <cmath>
#include <complex>
#include <iostream>
#define PI acos(-1)
using namespace std;

void fft(complex<double> *A, int n){
    if(n == 1) return;
    complex<double> A_O[n/2], A_E[n/2];
    for(int i = 0; i < n; i++){
        if(i%2 == 0) A_E[i/2] = A[i];
        else A_O[i/2] = A[i];
    }
    fft(A_O, n/2); fft(A_E, n/2);
    complex<double> w(1, 0), w_n(cos(2*PI/n), sin(2*PI/n)), tw(0,0);
    for(int k = 0; k < n/2; k++){ 
        tw = w*A_O[k];
        A[k] = A_E[k] + tw;
        A[k + n/2] = A_E[k] - tw;
        w = w*w_n;
    }
    return;
}

int main() {
    int t = 0;
    scanf("%d", &t);
    for(int j = 0; j < t; j++){
        int n = 0;
        scanf("%d", &n);
        int N = 1 ;
        while(N < n) N *= 2;
        //int N = pow(2, ceil(log2(n)));
        complex<double> coeffs[N];
        double re = 0, im = 0;
        for(int i = 0; i < n; i++){
            scanf("%lf %lf", &re, &im);
            coeffs[i].real(re); coeffs[i].imag(im);
        }
        for(int i = n; i < N; i++){
            coeffs[i].real(0); coeffs[i].imag(0);
        }
        fft(coeffs, N);
        for(int i = 0; i < N; i++){
            printf("(%.3lf,%.3lf)\n", coeffs[i].real(), coeffs[i].imag());
        }
        
    }
    return 0;
}

