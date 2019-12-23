typedef vector<vector<ll> > matrix;
matrix mul(matrix A, matrix B){
    matrix C(K, vector<ll>(K));
    lp(i,0, K) lp(j,0, K) lp(k,0, K)
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
    return C;
}
// Only Square Matrices
matrix pow(matrix A, ll p){
    if (p == 1)
        return A;
    if (p % 2)
        return mul(A, pow(A, p-1));
    matrix X = pow(A, p/2);
    return mul(X, X);
}