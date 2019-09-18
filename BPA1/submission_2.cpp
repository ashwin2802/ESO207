nclude <cmath>
#include <iostream>
#include <complex>
// #define PI acos(-1)
using namespace std;

typedef std::complex<long double> cplx;
const long double E = 0.001;
const long double PI = acos(-1);

void fft(cplx *A, int n){
    if(n == 1) return;
    cplx A_O[n/2], A_E[n/2];
    for(int i = 0; i < n; i++){
        if(i%2 == 0) A_E[i/2] = A[i];
        else A_O[i/2] = A[i];
    }
    fft(A_O, n/2); fft(A_E, n/2);
    cplx w(1, 0), w_n(cos(2*PI/n), sin(2*PI/n)), tw(0,0);
    for(int k = 0; k < n/2; k++){ 
        tw = w*A_O[k];
        A[k] = A_E[k] + tw;
        A[k + n/2] = A_E[k] - tw;
        w = w*w_n;
    }
    return;
}

void ifft(cplx *A, int n){
    if(n == 1) return;
    cplx A_O[n/2], A_E[n/2];
    for(int i = 0; i < n; i++){
        if(i%2 == 0) A_E[i/2] = A[i];
        else A_O[i/2] = A[i];
    }
    ifft(A_O, n/2); ifft(A_E, n/2);
    cplx w(1, 0), w_n(cos(2*PI/n), -sin(2*PI/n)), tw(0,0);
    for(int k = 0; k < n/2; k++){ 
        tw = w*A_O[k];
        A[k] = A_E[k] + tw;
        A[k + n/2] = A_E[k] - tw;
        w = w*w_n;
        // A[k] /= 2;
        // A[k + n/2] /= 2;
    }
    return;
}

int main() {
    int t = 0, n = 0;
    long double re = 0, im = 0;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        int N = 1;
        while(N < 2*n) N*=2;
        cplx a[N], b[N];
        for(int i=0; i<n; i++){
            scanf("%Lf %Lf", &re, &im);
            a[i].real(re); a[i].imag(im);
        }
        for(int i=0; i<n; i++){
            scanf("%Lf %Lf", &re, &im);
            b[i].real(re); b[i].imag(im);
        }
        for(int i=n; i<N; i++){
            a[i].real(0); a[i].imag(0);
            b[i].real(0); b[i].imag(0);
        }
        fft(a, N); fft(b, N);
        for(int i=0; i<N; i++) a[i] *= b[i];
        ifft(a, N);
        for(int i=0; i<N; i++) a[i] /= N;
        for(int i=0; i<N; i++){
            if(abs(a[i].real())<E) a[i].real(0);
            if(abs(a[i].imag())<E) a[i].imag(0);
            printf("(%0.3Lf,%0.3Lf)\n", a[i].real(), a[i].imag());
        }
    }
    return 0;
}

