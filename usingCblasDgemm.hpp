#include <cblas.h>


//     C    =         A      *     B     
// ^ [[...],     ^ [[...],      ^ [[...], 
// |  [...],   = |  [...],   *  |  [...], 
// m  ...        m  ...         k  ...    
// |  [...]]     |  [...]]      |  [...]] 
//   <-n->          <-k->          <-n->
// 
// YOU MUST CHECK TWICE BEFORE YOU USE 
// THIS FUNCTION
// CUZ THERE IS NO CHECKING INSIDE
void usingCblasDgemm(double* A, double* B, double* C,
                     int m, int n, int k) {
  double alpha = 1.;
  double beta = 0.;
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, k, 
                alpha, 
                A, k, 
                B, n, 
                beta, 
                C, n);
}