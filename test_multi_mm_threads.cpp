#define min(x,y) (((x) < (y)) ? (x) : (y))

#include <stdio.h>
#include <stdlib.h>
#include "usingCblasDgemm.hpp"

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    double *A, *B, *C;
    int m, n, k, i, j;
    int K, N;
    double alpha, beta;


    m = 3, k = 5, n = 2;
    K = k*6;
    N = n*6;
    printf (" Initializing data for matrix multiplication C=A*B for matrix \n"
            " A(%ix%i) and matrix B(%ix%i)\n\n", m, k, k, n);

    printf (" Allocating memory for matrices aligned on 64-byte boundary for better \n"
            " performance \n\n");
    A = (double *)malloc( m * K *sizeof( double ) );
    B = (double *)malloc( k * n*sizeof( double ) );
    C = (double *)malloc( m * N*sizeof( double ) );

    printf (" Intializing matrix data \n\n");
    for (i = 0; i < (m*K); i++) {
        A[i] = (double)(i+1);
    }

    for (i = 0; i < (k*n); i++) {
        B[i] = (double)(i+1);
    }

    for (i = 0; i < (m*N); i++) {
        C[i] = 0.0;
    }



    //
    const int N_THREAD_PER_GRID = 2;
    vector<thread> threads;
    for(int n_grid=0; n_grid<6/N_THREAD_PER_GRID; ++n_grid) {
      threads.clear();


      // LOADING GRID
      for(int n_thread=0; n_thread<N_THREAD_PER_GRID; ++n_thread) {
        i = n_grid*N_THREAD_PER_GRID + n_thread;
        threads.push_back( thread(usingCblasDgemm, &(A[i*m*k]), B, &(C[i*m*n]), m, n, k) );
      }

      // PROC GRID
      for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
      // for_each(threads.begin(), threads.end(), bind());
    }

    // for(int i=0; i<6; ++i) {
    //     usingCblasDgemm(&(A[i*m*k]), B, &(C[i*m*n]), m, n, k);
    // }




    printf (" Top left corner of matrix A: \n");
    for (i=0; i<min(m,6); i++) {
      for (j=0; j<min(k,6); j++) {
        printf ("%12.0f", A[j+i*k]);
      }
      printf ("\n");
    }

    printf ("\n Top left corner of matrix B: \n");
    for (i=0; i<min(k,6); i++) {
      for (j=0; j<min(n,6); j++) {
        printf ("%12.0f", B[j+i*n]);
      }
      printf ("\n");
    }
    
    for(int ii=0; ii<6; ++ii) {
      printf ("\n Top left corner of matrix C: \n");
      for (i=0; i<min(m,6); i++) {
        for (j=0; j<min(n,6); j++) {
          printf ("%12.5G", (&(C[ii*m*n])) [j+i*n]);
        }
        printf ("\n");
      }
    }

    printf ("\n Deallocating memory \n\n");
    free(A);
    free(B);
    free(C);

    printf (" Example completed. \n\n");
    return 0;

    /*
    # python test script
    import numpy as np
    a = np.array(range(1, 16*6))
    for i in range(6):
      aa = a[15*i: 15*i+15]
      aa = aa.reshape((3, 5))
      b = np.array(range(1, 11))
      b = b.reshape((5, 2))
      print np.dot(aa, b)
    */
}
